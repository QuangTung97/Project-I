#include <logic/factory/plane.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/events.hpp>
#include <logic/actor/sound.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/plane.hpp>
#include <logic/actor/sprite.hpp>
#include <logic/actor/graphics_image.hpp>
#include <vector>
#include <random>

namespace tung {
namespace factory {

const std::string& get_random_jet_image() {
    static std::random_device device;
    static const std::vector<std::string> jet_images = {
        "assets/jet1.png",
        "assets/jet2.png",
        "assets/jet3.png"
    };
    std::uniform_int_distribution<int> dist(0, 2);
    return jet_images[dist(device)];
}

std::weak_ptr<actor::Plane> Plane::new_plane(bool is_fighter) {
    auto id = actor::IdGenerator::new_id();
    auto a = std::make_shared<actor::Actor>(id);

    float x = -2, y = 0;
    const float radius = 0.2;
    const float velocity = 0.8;

    auto sound = std::make_shared<actor::Sound>(sound_manager_);
    // sound->add_sound(0, "assets/plane_fly.mp3");
    sound->add_sound(1, "assets/plane_explode.mp3");
    a->add_component(std::move(sound));

    auto image = std::make_shared<actor::GraphicsImage>(
        x, y,
        image_drawable_factory_, root_,
        2 * radius, get_random_jet_image()
    );
    a->add_component(std::move(image));

    auto collision = std::make_shared<actor::CircleCollision>(x, y, radius);
    a->add_component(std::move(collision));

    auto sprite = std::make_shared<actor::Sprite>(
        root_, sprite_factory_, process_manager_
    );
    sprite->add_sprite(0, "assets/explosion1.png", 6, 8, 2 * radius);
    a->add_component(std::move(sprite));

    auto plane = std::make_shared<actor::Plane>(
        event_manager_, process_manager_, 
        x, y, velocity, is_fighter);
    a->add_component(plane);

    GameLogic::get().add_actor(a);
    actor::CreatedEvent actor_created{a->get_id()};
    event_manager_.trigger(actor_created);
    return plane;
}

} // namespace factory
} // namespace tung