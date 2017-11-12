#include <logic/game/plane.hpp>
#include <logic/actor/events.hpp>
#include <logic/abstract/call_once_process.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/sound.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/sprite.hpp>
#include <logic/actor/graphics_image.hpp>
#include <random>

namespace tung {
namespace game {

static std::random_device rd;
static std::mt19937 generator{rd()};
static std::uniform_real_distribution<float> uniform(0, 1);
static std::uniform_real_distribution<float> y_uniform(-0.2, 0.8);
static std::uniform_int_distribution<int> uniform_int02(0, 2);
static std::uniform_int_distribution<int> uniform_int01(0, 1);

//-----------------
// FlyProcess
//-----------------
void FlyProcess::on_init() {
    Process::on_init();
    plane_.dx_ = 0.0f;

    // Plane's Sound
    actor::SoundStartedEvent event{plane_.get_id(), 0};
    plane_.state_manager_.get_event_manager().trigger(event);
}

void FlyProcess::on_update(milliseconds dt) {
    float dx = plane_.velocity_ * dt.count() / 1000.0f;
    plane_.x_ += dx;
    plane_.dx_ += dx;
    if (plane_.dx_ > plane_.max_distance_) {
        succeed();
        return;
    }

    actor::MoveEvent event{plane_.get_id(), plane_.x_, plane_.y_};
    plane_.state_manager_.get_event_manager().trigger(event);
}

void FlyProcess::on_success() {
    // Plane's Sound
    actor::SoundEndedEvent event{plane_.get_id(), 0};
    plane_.state_manager_.get_event_manager().queue(event);

    // Destroy actor
    actor::DestroyEvent destroy_event{plane_.get_id()};
    plane_.state_manager_.get_event_manager().queue(destroy_event);
}

void FlyProcess::on_fail() {
    // Plane's Sound
    actor::SoundEndedEvent event{plane_.get_id(), 0};
    plane_.state_manager_.get_event_manager().queue(event);
}

void FlyProcess::on_abort() {
    // Plane's Sound
    actor::SoundEndedEvent event{plane_.get_id(), 0};
    plane_.state_manager_.get_event_manager().queue(event);

    // Destroy actor
    actor::DestroyEvent destroy_event{plane_.get_id()};
    plane_.state_manager_.get_event_manager().queue(destroy_event);
}

//------------------------------
// Plane
//------------------------------
Plane::Plane(state::Manager& state_manager, bool is_fighter) 
: state_manager_{state_manager}, is_fighter_{is_fighter},
    actor::Actor{actor::IdGenerator::new_id()}
{
    fly_process_ = std::make_shared<FlyProcess>(*this);
    destroy_plane_ = std::make_shared<CallOnceProcess>(2s, [this]() {
        actor::DestroyEvent destroy_actor{get_id()};
        state_manager_.get_event_manager().queue(destroy_actor);
    });
}

const std::string& get_random_fighter_image() {
    static const std::vector<std::string> jet_images = {
        "assets/fighter1.png",
        "assets/fighter2.png",
        "assets/fighter3.png"
    };
    return jet_images[uniform_int02(generator)];
}

const std::string& get_random_commercial_plane_image() {
    static const std::vector<std::string> images = {
        "assets/commercial_plane1.png",
        "assets/commercial_plane2.png"
    };

    return images[uniform_int01(generator)];
}

void Plane::init() {
    const float radius = 0.15;
    const float velocity = 1.2;
    const float commercial_plane_prob = 0.2;
    const float width = radius * 1.6 * 2;
    const float height = radius * 2;

    x_ = -1.5f;
    y_ = y_uniform(generator);

    auto sound = std::make_shared<actor::Sound>(
        state_manager_.get_sound_manager());
    // sound->add_sound(0, "assets/plane_fly.mp3");
    sound->add_sound(1, "assets/plane_explode.mp3");
    add_component(std::move(sound));

    float prob = uniform(generator);
    if (prob <= commercial_plane_prob) {
        auto image = std::make_shared<actor::GraphicsImage>(
            x_, y_,
            state_manager_.get_image_factory(), 
            state_manager_.get_root(),
            height, get_random_commercial_plane_image()
        );
        add_component(std::move(image));

        auto collision = std::make_shared<actor::RectangleCollision>(
            x_, y_, width, height * 0.3);
        add_component(std::move(collision));
    }
    else {
        auto image = std::make_shared<actor::GraphicsImage>(
            x_, y_,
            state_manager_.get_image_factory(), 
            state_manager_.get_root(),
            height * 0.9, get_random_fighter_image()
        );
        add_component(std::move(image));

        auto collision = std::make_shared<actor::CircleCollision>(x_, y_, radius);
        add_component(std::move(collision));
    }

    auto sprite = std::make_shared<actor::Sprite>(
        state_manager_.get_root(), 
        state_manager_.get_sprite_factory(),
        state_manager_.get_process_manager()
    );
    sprite->add_sprite(0, "assets/explosion1.png", 6, 8, 2 * radius);
    add_component(std::move(sprite));

    GameLogic::get().add_actor(shared_from_this());
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);
}

void Plane::start_fly() {
    fly_process_->reset();
    state_manager_.get_process_manager().attach_process(fly_process_);
}

void Plane::end_fly() {
    fly_process_->fail();
}

void Plane::explode() {
    fly_process_->fail();
    actor::DisableCollisionEvent disable_collision{get_id()};
    state_manager_.get_event_manager().trigger(disable_collision);

    // Explosion's Sound
    actor::SoundStartedEvent sound_started{get_id(), 1};
    state_manager_.get_event_manager().trigger(sound_started);

    actor::SpriteStartedEvent sprite_started{get_id(), 0};
    state_manager_.get_event_manager().trigger(sprite_started);

    actor::GraphicsImageHideEvent hide_event{get_id()};
    state_manager_.get_event_manager().trigger(hide_event);

    state_manager_.get_process_manager().attach_process(destroy_plane_);
}

} // namespace game
} // namespace tung