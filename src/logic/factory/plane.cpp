#include <logic/factory/plane.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/events.hpp>
#include <logic/actor/sound.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/plane.hpp>
#include <logic/actor/sprite.hpp>

#include <iostream>

namespace tung {
namespace factory {

actor::ActorId Plane::new_plane(bool is_fighter) {
    auto id = actor::IdGenerator::new_id();
    auto a = std::make_shared<actor::Actor>(id);

    float x = -2, y = 0;
    const float radius = 0.2;
    const float velocity = 0.3;

    auto sound = std::make_shared<actor::Sound>(sound_manager_);
    // sound->add_sound(0, "assets/plane_fly.mp3");
    sound->add_sound(1, "assets/plane_explode.mp3");
    a->add_component(std::move(sound));


    auto collision = std::make_shared<actor::CircleCollision>(x, y, radius);
    a->add_component(std::move(collision));

    auto sprite = std::make_shared<actor::Sprite>(
        root_, sprite_factory_, process_manager_
    );

    auto plane = std::make_shared<actor::Plane>(
        event_manager_, process_manager_, 
        x, y, velocity, is_fighter);
    a->add_component(std::move(plane));

    GameLogic::get().add_actor(a);
    actor::CreatedEvent actor_created{a->get_id()};
    event_manager_.trigger(actor_created);
    return id;
}

} // namespace factory
} // namespace tung