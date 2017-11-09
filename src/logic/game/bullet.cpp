#include <logic/game/bullet.hpp>
#include <logic/actor/events.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/game_logic.hpp>
#include <cmath>

namespace tung {
namespace game {

class BulletFlyProcess: public Process {
private:
    Bullet& bullet_;

protected:
    void on_init() override {
        Process::on_init();
    }

    void on_update(milliseconds dt) override {
        bullet_.x_ += bullet_.vx_ * dt.count() / 1000.0f;
        bullet_.y_ += bullet_.vy_ * dt.count() / 1000.0f;

        if (std::abs(bullet_.x_) >= 2.0f ||
            std::abs(bullet_.y_) >= 3.0f) {
            succeed();
            return;
        }

        actor::MoveEvent move_event{bullet_.get_id(), bullet_.x_, bullet_.y_};
        bullet_.state_manager_.get_event_manager().trigger(move_event);
    }

    void on_success() override {
        actor::DestroyEvent destroy_event{bullet_.get_id()};
        bullet_.state_manager_.get_event_manager().queue(destroy_event);
    }

    void on_fail() override {
        on_success();
    }

public:
    BulletFlyProcess(Bullet& bullet)
    : bullet_{bullet} {}
};

Bullet::Bullet(state::Manager& state_manager, 
    float x, float y, float degree)
: actor::Actor{actor::IdGenerator::new_id()},
    state_manager_{state_manager}
{
    x_ = x;
    y_ = y;
    const float pi = 3.141592654;
    float radian = degree / 180 * pi;
    vx_ = velocity_ * std::cos(radian);
    vy_ = velocity_ * std::sin(radian);

    fly_process_ = std::make_shared<BulletFlyProcess>(*this);
}

void Bullet::init() {
    float radius = 0.03f;

    auto image = std::make_shared<actor::GraphicsImage>(
        x_, y_,
        state_manager_.get_image_factory(),
        state_manager_.get_root(),
        0.08f, "assets/bullet.png"
    );
    add_component(std::move(image));

    auto collision = std::make_shared<actor::CircleCollision>(
        x_, y_, radius
    );
    add_component(std::move(collision));

    GameLogic::get().add_actor(shared_from_this());
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);
}

void Bullet::start_fly() {
    fly_process_->reset();
    state_manager_.get_process_manager()
        .attach_process(fly_process_);
}

void Bullet::end_fly() {
    fly_process_->fail();
}

} // namespace game
} // namespace tung