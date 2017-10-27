#ifndef LOGIC_COLLISION_COMPONENT_HPP
#define LOGIC_COLLISION_COMPONENT_HPP

#include "actor_component.hpp"
#include <logic/event.hpp>
#include <logic/actor.hpp>

namespace tung {

extern EventType<7001> ACTOR_COLLIDE;

class ActorCollideEvent: public EventData {
private:
    ActorId id_;

public:
    ActorCollideEvent(TimePoint time_point, ActorId id)
    : EventData{time_point, ACTOR_COLLIDE}, id_{id} {}

    ActorId get_id() const { return id_; }
};

class CollisionComponent: public ActorComponent {
protected:
    float x_, y_;
    enum class Type {
        CIRCLE,
        RECTANGLE
    };

public:
    CollisionComponent(float x, float y)
    : x_{x}, y_{y} {}

    ActorComponentId get_id() const override {
        return ActorComponentId::COLLISION;
    }

    virtual Type get_type() const = 0;

    virtual bool is_collided(const CollisionComponent& other) = 0;

    virtual ~CollisionComponent() {}
};

class CircleCollisionComponent: public CollisionComponent {
protected:
    float radius_;

public:
    CircleCollisionComponent(float x, float y, float radius)
    : CollisionComponent(x, y), radius_{radius} {}

    Type get_type() const override {
        return Type::CIRCLE;
    }

    bool is_collided(const CollisionComponent& other) override;
};

} // namespace tung

#endif