#include <logic/system/sound.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>

namespace tung {
namespace system {

Sound::Sound(IEventManager& manager)
: manager_{manager} 
{
    auto actor_created = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::CreatedEvent&>(event_);
        auto tmp_actor = GameLogic::get().get_actor(event.get_id()).lock();
        if (tmp_actor) {
            auto comp = tmp_actor->get_component<actor::Sound>().lock();
            if (comp)
                components_[event.get_id()] = comp;
        }
    };

    auto actor_destroy = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::DestroyEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->set_owner(nullptr);
            components_.erase(find_it);
        }
    };

    auto sound_started = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::SoundStartedEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->start(event.get_index());
        }
    };

    auto sound_ended = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::SoundEndedEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->end(event.get_index());
        }
    };

    actor_created_listener_ = actor_created;
    actor_destroy_listener_ = actor_destroy;
    sound_started_listener_ = sound_started;
    sound_ended_listener_ = sound_ended;

    manager_.add_listener(actor::EVENT_CREATED, actor_created_listener_);
    manager_.add_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    manager_.add_listener(actor::EVENT_SOUND_STARTED, sound_started_listener_);
    manager_.add_listener(actor::EVENT_SOUND_ENDED, sound_ended_listener_);
}

Sound::~Sound() {
    manager_.remove_listener(actor::EVENT_SOUND_ENDED, sound_ended_listener_);
    manager_.remove_listener(actor::EVENT_SOUND_STARTED, sound_started_listener_);
    manager_.remove_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    manager_.remove_listener(actor::EVENT_CREATED, actor_created_listener_);
}

} // namespace system
} // namespace tung