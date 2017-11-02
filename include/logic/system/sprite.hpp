#ifndef LOGIC_SYSTEM_SPRITE_HPP
#define LOGIC_SYSTEM_SPRITE_HPP

#include <logic/abstract/event_manager.hpp>
#include <logic/actor/sprite.hpp>
#include <unordered_map>

namespace tung {
namespace system {

class Sprite {
private:
    IEventManager& manager_;
    EventListener actor_created_listener_;
    EventListener actor_destroy_listener_;
    EventListener actor_move_listener_;
    EventListener sprite_started_listener_;
    EventListener sprite_ended_listener_;

    typedef std::weak_ptr<actor::Sprite> WeakPtr;
    typedef std::unordered_map<actor::ActorId, WeakPtr> 
        ActorComponentMap;

    ActorComponentMap components_;

public:
    Sprite(IEventManager& manager);

    ~Sprite();
};

} // namespace system
} // namespace tung

#endif