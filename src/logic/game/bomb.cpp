#include <logic/game/bomb.hpp>
#include <logic/actor/events.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/game_logic.hpp>

namespace tung {
namespace game {

typedef std::weak_ptr<Bomb> WeakBombPtr;

class BombFlyProcess: public Process {
private:
    WeakBombPtr bomb_;

protected: 
    void on_update(milliseconds dt) override {
        auto bomb = bomb_.lock();
        if (!bomb) {
            fail();
            return;
        }

        bomb->y_ -= bomb->velocity_ * dt.count() / 1000.f;

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
        on_success();
    }

public:
    BombFlyProcess(WeakBombPtr bomb)
    : bomb_{std::move(bomb)} {}

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

}

} // namespace game
} // namespace tung