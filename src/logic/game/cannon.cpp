#include <logic/game/cannon.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>
#include <logic/game/bullet.hpp>

namespace tung {
namespace game {

void Cannon::init() {
    auto base = std::make_shared<actor::Actor>(actor::IdGenerator::new_id());
    base_id_ = base->get_id();

    auto head = std::make_shared<actor::Actor>(actor::IdGenerator::new_id());
    head_id_ = head->get_id();

    const float x = 0, y = -1;
    const float base_height = 0.2;
    const float head_height = 0.13;

    auto head_image = std::make_shared<actor::GraphicsImage>(
        x, y, 
        state_manager_.get_image_factory(),
        state_manager_.get_upper_group(),
        head_height, "assets/cannon_head.png"
    );
    head->add_component(std::move(head_image));

    auto base_image = std::make_shared<actor::GraphicsImage>(
        x, y, 
        state_manager_.get_image_factory(),
        state_manager_.get_upper_group(),
        base_height, "assets/cannon_base.png"
    );
    base->add_component(std::move(base_image));


    GameLogic::get().add_actor(shared_from_this());
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);

    GameLogic::get().add_actor(head);
    actor::CreatedEvent head_created{head_id_};
    state_manager_.get_event_manager().trigger(head_created);

    GameLogic::get().add_actor(base);
    actor::CreatedEvent base_created{base_id_};
    state_manager_.get_event_manager().trigger(base_created);

    rotate(90);
}

void Cannon::rotate(float degree) {
    head_angle_ = degree;
    actor::RotateEvent rotate_head{head_id_, degree};
    state_manager_.get_event_manager().trigger(rotate_head);
}

actor::ActorId Cannon::shot() {
    auto bullet = std::make_shared<game::Bullet>(
        state_manager_, 0, -1, head_angle_);
    bullet->init();
    bullet->start_fly();
    return bullet->get_id();
}

Cannon::~Cannon() {
    actor::DestroyEvent destroy_head{head_id_};
    state_manager_.get_event_manager().trigger(destroy_head);

    actor::DestroyEvent destroy_base{base_id_};
    state_manager_.get_event_manager().trigger(destroy_base);
}

} // namespace game
} // namespace tung