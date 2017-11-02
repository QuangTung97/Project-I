#ifndef SOUND_SYSTEM_HPP
#define SOUND_SYSTEM_HPP

#include <logic/abstract/event_manager.hpp>
#include <logic/actor/sound.hpp>
#include <unordered_map>

namespace tung {
namespace system {

class Sound {
private:
    IEventManager& manager_;
    EventListener actor_created_listener_;
    EventListener actor_destroy_listener_;
    EventListener sound_started_listener_;
    EventListener sound_ended_listener_;

    typedef std::weak_ptr<actor::Sound> WeakPtr;
    typedef std::unordered_map<actor::ActorId, WeakPtr> 
        ActorComponentMap;

    ActorComponentMap components_;

public:
    Sound(IEventManager& manager);

    ~Sound();
};

} // namespace system
} // namespace tung

#endif