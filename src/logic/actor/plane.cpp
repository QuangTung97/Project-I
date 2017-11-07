#include <logic/actor/actor.hpp>
#include <logic/actor/plane.hpp>
#include <logic/actor/events.hpp>

#include <iostream>

namespace tung {
namespace actor {

//-----------------
// FlyProcess
//-----------------
void FlyProcess::on_init() {
    Process::on_init();

    // Plane's Sound
    SoundStartedEvent event{owner_.get_actor_id(), 0};
    owner_.event_manager_.trigger(event);
}

void FlyProcess::on_update(milliseconds dt) {
    float dx = owner_.velocity_ * dt.count() / 1000.0f;
    owner_.x_ += dx;
    owner_.dx_ += dx;
    if (owner_.dx_ > owner_.max_distance_) {
        succeed();
        return;
    }

    MoveEvent event{owner_.get_actor_id(), owner_.x_, owner_.y_};
    owner_.event_manager_.trigger(event);
}

void FlyProcess::on_success() {
    // Plane's Sound
    SoundEndedEvent event{owner_.get_actor_id(), 0};
    owner_.event_manager_.queue(event);

    // Destroy actor
    actor::DestroyEvent destroy_event{owner_.get_actor_id()};
    owner_.event_manager_.queue(destroy_event);
}

void FlyProcess::on_fail() {
    // Plane's Sound
    SoundEndedEvent event{owner_.get_actor_id(), 0};
    owner_.event_manager_.queue(event);
}

//-------------------------------
// Wait to Destroy Plane Process
//-------------------------------
void WaitToDestroyPlaneProcess::on_init() {
    Process::on_init();
    elapsed_time_ = 0ms;
}

void WaitToDestroyPlaneProcess::on_update(milliseconds dt) {
    elapsed_time_ += dt;
    if (elapsed_time_ >= wait_time_)
        succeed();
}

void WaitToDestroyPlaneProcess::on_success() {
    actor::DestroyEvent destroy_actor{owner_.get_actor_id()};
    owner_.event_manager_.queue(destroy_actor);
}

//-------------------------------
// Plane
//-------------------------------
const ComponentId Plane::COMPONENT_ID = ComponentId::PLANE;

Plane::Plane(IEventManager& event_manager, ProcessManager& process_manager, 
    float x, float y, float velocity, bool is_fighter) 
: event_manager_{event_manager}, process_manager_{process_manager},
    x_{x}, y_{y}, velocity_{velocity}, is_fighter_{is_fighter} 
{
    fly_process_ = std::make_shared<FlyProcess>(*this);
    destroy_plane_ = std::make_shared<WaitToDestroyPlaneProcess>(*this, 2s);
}

void Plane::start_fly() {
    fly_process_->reset();
    process_manager_.attach_process(fly_process_);
}

void Plane::end_fly() {
    fly_process_->fail();
}

void Plane::explode() {
    fly_process_->fail();
    // Explosion's Sound
    actor::SoundStartedEvent sound_started{get_actor_id(), 1};
    event_manager_.queue(sound_started);

    actor::SpriteStartedEvent sprite_started{get_actor_id(), 0};
    event_manager_.queue(sprite_started);

    process_manager_.attach_process(destroy_plane_);
}

} // namespace actor
} // namespace tung