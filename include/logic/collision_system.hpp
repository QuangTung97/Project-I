#ifndef LOGIC_COLLISION_SYSTEM_HPP
#define LOGIC_COLLISION_SYSTEM_HPP

#include <logic/abstract/event_manager.hpp>
#include <logic/abstract/timer.hpp>
#include <logic/actor_component.hpp>
#include <logic/actor.hpp>
#include <unordered_map>

namespace tung {

class CollisionSystem {
private:
    IEventManager& manager_;
    ITimer& timer_;
    EventListener actor_created_listener_;
    EventListener actor_destroy_listener_;
    typedef std::unordered_map<ActorId, WeakActorComponentPtr> 
        ActorComponents;

    ActorComponents actor_components_;

public:
    CollisionSystem(IEventManager& manager, ITimer& timer);

    void update();

    ~CollisionSystem();
};

} // namespace tung

#endif