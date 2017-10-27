#ifndef LOGIC_COLLISION_COMPONENT_HPP
#define LOGIC_COLLISION_COMPONENT_HPP

#include "actor_component.hpp"
#include <logic/event.hpp>
#include <logic/actor.hpp>

namespace tung {

extern EventType<7000> ACTORS_COLLIDE;

class ActorsCollideEvent: public EventData {
private:
    ActorId id1_, id2_;

public:
    ActorsCollideEvent(TimePoint time_point, ActorId id1, ActorId id2)
    : EventData{time_point, ACTORS_COLLIDE}, id1_{id1}, id2_{id2} {}
};

class CollisionComponent: public ActorComponent {
private:
    float x_, y_;
    float radius_;
    friend class CollisionSystem;

public:
    CollisionComponent(float x, float y, float radius);

    ~CollisionComponent();
};

} // namespace tung

#endif