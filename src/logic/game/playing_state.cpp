#include <logic/game/playing_state.hpp>
#include <logic/game/manager.hpp>
#include <logic/game/bullet.hpp>
#include <logic/game/plane.hpp>
#include <graphics/gl/glfw.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>
#include <cmath>

namespace tung {
namespace state {

class PlaneGenerator: public Process {
private:
    PlayingState& state_;
    milliseconds elapsed_time_;
    milliseconds cycle_;

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
        cycle_ = 1000ms;
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        if (elapsed_time_ >= cycle_) {
            elapsed_time_ = 0ms;
            auto plane = std::make_shared<game::Plane>(
                state_.manager_, true
            );
            plane->init();
            plane->start_fly();
            state_.planes_.insert(plane->get_id());
        }
    }

    void on_success() override {
    }

    void on_fail() override {
    }

public:
    PlaneGenerator(PlayingState& state)
    : state_{state} {}
};


PlayingState::PlayingState(Manager& manager)
: GameState(manager) 
{
    background_ = manager_.get_image_factory()
        .new_drawable("assets/playing_background.png", 2);
    plane_generator_ = std::make_shared<PlaneGenerator>(*this);

    auto plane_destroy = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::DestroyEvent&>(event_);
        // remove plane
        auto find_it = planes_.find(event.get_id());
        if (find_it != planes_.end()) {
            planes_.erase(find_it);
        }

        // remove bullet
        auto it = bullets_.find(event.get_id());
        if (it != bullets_.end()) {
            bullets_.erase(it);
        }
    };
    plane_destroy_listener_ = plane_destroy;

    auto collide = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::CollideEvent&>(event_);
        auto find_it = planes_.find(event.get_id());
        auto bullet_it = bullets_.find(event.get_collide_width_id());
        if (find_it != planes_.end() && bullet_it != bullets_.end()) {
            auto ptr = GameLogic::get().get_actor(event.get_id()).lock();
            if (ptr) {
                auto plane = std::dynamic_pointer_cast<game::Plane>(ptr);
                plane->explode();
            }
        }

        auto it = bullets_.find(event.get_id());
        if (it != bullets_.end()) {
            auto ptr = GameLogic::get().get_actor(event.get_id()).lock();
            if (ptr) {
                auto bullet = std::dynamic_pointer_cast<game::Bullet>(ptr);
                bullet->end_fly();
            }
        }
    };
    collide_listener_ = collide;
}

void PlayingState::entry() {
    manager_.get_process_manager().attach_process(plane_generator_);
    manager_.get_event_manager().add_listener(actor::EVENT_DESTROY, 
        plane_destroy_listener_);
    manager_.get_event_manager().add_listener(actor::EVENT_COLLIDE, 
        collide_listener_);

    manager_.get_root()->attach_drawable(background_);
    cannon_ = std::make_shared<game::Cannon>(manager_);
    cannon_->init();
}

void PlayingState::exit() {
    // Destroy cannon
    cannon_ = nullptr;

    // Destroy planes
    auto planes = planes_;
    for (auto& plane: planes) {
        actor::DestroyEvent event{plane};
        manager_.get_event_manager().trigger(event);
    }

    // Destroy bullets
    auto bullets = bullets_;
    for (auto& bullet: bullets) {
        actor::DestroyEvent event{bullet};
        manager_.get_event_manager().trigger(event);
    }

    manager_.get_event_manager().remove_listener(actor::EVENT_DESTROY, 
        plane_destroy_listener_);
    manager_.get_event_manager().remove_listener(actor::EVENT_COLLIDE, 
        collide_listener_);

    manager_.get_root()->detach_drawable(background_);
}

bool PlayingState::on_mouse_event(MouseButton button,
    MouseEventType type, float x, float y) 
{
    if (button == MouseButton::LEFT && type == MouseEventType::DOWN) {
        float height = GLFW::get_screen_height();
        float width = GLFW::get_screen_width();
        float ux = x - width / 2;
        float uy = height - y;
        if (ux != 0) {
            float radian = std::atan(uy / ux);
            float degree = radian * 180 / 3.141592654;
            if (degree < 0)
                degree = 180 + degree;
            cannon_->rotate(degree);
            auto bullet_id = cannon_->shot();
            bullets_.insert(bullet_id);
        }
        return true;
    }
    return true;
}

} // namespace state
} // namespace tung