#include <logic/game/plane.hpp>
#include <logic/actor/events.hpp>
#include <logic/abstract/call_once_process.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/sound.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/sprite.hpp>
#include <logic/actor/graphics_image.hpp>

namespace tung {
namespace game {

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

void Plane::init() {
    x_ = -1.5f;
    y_ = 0;
    const float radius = 0.2;
    const float velocity = 0.8;

    auto sound = std::make_shared<actor::Sound>(
        state_manager_.get_sound_manager());
    // sound->add_sound(0, "assets/plane_fly.mp3");
    sound->add_sound(1, "assets/plane_explode.mp3");
    add_component(std::move(sound));

    auto image = std::make_shared<actor::GraphicsImage>(
        x_, y_,
        state_manager_.get_image_factory(), 
        state_manager_.get_root(),
        2 * radius, get_random_jet_image()
    );
    add_component(std::move(image));

    auto collision = std::make_shared<actor::CircleCollision>(x_, y_, radius);
    add_component(std::move(collision));

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