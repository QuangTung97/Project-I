#include <logic/game/bomb.hpp>
#include <logic/actor/events.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/sprite.hpp>
#include <logic/actor/sound.hpp>
#include <logic/abstract/call_once_process.hpp>
#include <logic/actor/collision.hpp>
#include <cmath>

namespace tung {
namespace game {

float normalize(float degree) {
    int times = degree / 360;
    return degree - times * 360;
}

typedef std::weak_ptr<Bomb> WeakBombPtr;

class BombFlyProcess: public Process {
private:
    WeakBombPtr bomb_;
    milliseconds elapsed_time_ = 0s;
    float x0_, y0_;
    float vx_, vy_;
    float degree_;

protected: 
    void on_init() override {
        Process::on_init();
        auto bomb = bomb_.lock();
        if (!bomb) {
            succeed();
            return;
        }
        actor::RotateEvent rotate_event{bomb->get_id(), degree_};
        bomb->state_manager_.get_event_manager().trigger(rotate_event);
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        auto bomb = bomb_.lock();
        if (!bomb) {
            succeed();
            return;
        }


        bomb->x_ = x0_ + vx_ * elapsed_time_.count() / 1000.0f;
        bomb->y_ = y0_ + vy_ * elapsed_time_.count() / 1000.0f;

        if (bomb->y_ < -1) {
            succeed();
            return;
        }

        actor::MoveEvent move_event{bomb->get_id(), bomb->x_, bomb->y_};
        bomb->state_manager_.get_event_manager().trigger(move_event);
    }

    void on_success() override {
        auto bomb = bomb_.lock();
        if (bomb) {
            actor::DestroyEvent destroy_event{bomb->get_id()};
            bomb->state_manager_.get_event_manager().trigger(destroy_event);
        }
    }

    void on_fail() override {
    }

    void on_abort() override {
        on_success();
    }

public:
    BombFlyProcess(WeakBombPtr bomb)
    : bomb_{std::move(bomb)} {
        auto ptr = bomb_.lock();
        const float cannon_x = 0;
        const float cannon_y = -1;
        if (ptr) {
            x0_ = ptr->x_;
            y0_ = ptr->y_;
            float dx = cannon_x - x0_;
            float dy = cannon_y - y0_;
            float d = std::sqrt(dx*dx + dy*dy);
            vx_ = dx / d * ptr->velocity_;
            vy_ = dy / d * ptr->velocity_;

            degree_ = std::acos(dx / d) * 180 / M_PI;
            if (dy < 0) {
                degree_ = -degree_;
            }
            degree_ = normalize(degree_ + 90);
        }
    }

};

Bomb::Bomb(state::Manager& state_manager, float x, float y)
: actor::Actor(actor::IdGenerator::new_id()), 
    state_manager_{state_manager}, x_{x}, y_{y} {}

void Bomb::init() {
    auto self = std::dynamic_pointer_cast<Bomb>(
        shared_from_this()
    );

    auto graphics = std::make_shared<actor::GraphicsImage>(
        x_, y_,
        state_manager_.get_image_factory(),
        state_manager_.get_root(),
        height_, "assets/bomb.png"
    );
    add_component(std::move(graphics));

    auto sound = std::make_shared<actor::Sound>(
        state_manager_.get_asset_manager());
    sound->add_sound(1, "assets/plane_explode.mp3");
    add_component(std::move(sound));

    auto sprite = std::make_shared<actor::Sprite>(
        state_manager_.get_root(), 
        state_manager_.get_sprite_factory(),
        state_manager_.get_process_manager()
    );
    sprite->add_sprite(0, "assets/explosion1.png", 6, 8, height_ * 1.2f);
    add_component(std::move(sprite));

    /*
    auto collision = std::make_shared<actor::RectangleCollision>(
        x_, y_, height_ * 170.0f / 515.0f, height_
    );
    */
    auto collision = std::make_shared<actor::CircleCollision>(
        x_, y_, height_ / 2
    );
    add_component(std::move(collision));

    GameLogic::get().add_actor(shared_from_this());
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);
}

void Bomb::start_fly() {
    flying_ = true;

    auto self = std::dynamic_pointer_cast<Bomb>(
        shared_from_this()
    );

    fly_process_ = std::make_shared<BombFlyProcess>(self);
    state_manager_.get_process_manager().attach_process(fly_process_);
}

void Bomb::end_fly() {
    fly_process_->succeed();
    fly_process_ = nullptr;
}

void Bomb::explode() {
    fly_process_->fail();
    fly_process_ = nullptr;

    actor::DisableCollisionEvent disable_collision{get_id()};
    state_manager_.get_event_manager().trigger(disable_collision);

    actor::GraphicsImageHideEvent hide_event{get_id()};
    state_manager_.get_event_manager().trigger(hide_event);

    // Explosion's Sound
    actor::SoundStartedEvent sound_started{get_id(), 1};
    state_manager_.get_event_manager().trigger(sound_started);

    actor::SpriteStartedEvent sprite_started{get_id(), 0};
    state_manager_.get_event_manager().trigger(sprite_started);

    std::weak_ptr<Bomb> self = std::dynamic_pointer_cast<Bomb>(
        shared_from_this()
    );

    auto destroy_process = std::make_shared<CallOnceProcess>(2500ms, 
        [self=std::move(self)] {
        auto this_ = self.lock();
        if (this_) {
            actor::DestroyEvent destroy_actor{this_->get_id()};
            this_->state_manager_.get_event_manager().trigger(destroy_actor);
        }
    });

    state_manager_.get_process_manager().attach_process(std::move(destroy_process));
}

} // namespace game
} // namespace tung
