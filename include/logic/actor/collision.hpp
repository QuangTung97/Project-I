#ifndef LOGIC_ACTOR_COLLISION_HPP
#define LOGIC_ACTOR_COLLISION_HPP

#include <logic/basic/event.hpp>
#include "actor.hpp"
#include "component.hpp"

namespace tung {

namespace system {
class Collision;
}

namespace actor {

bool is_rectangle_circle_collided(float rx, float ry, 
    float width, float height, 
    float cx, float cy, float radius);

bool is_two_rectangle_collided(
    float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2);

class Collision: public Component {
protected:
    float x_, y_;
    enum class Type {
        CIRCLE,
        RECTANGLE
    };
    friend class tung::system::Collision;
    bool enabled_ = true;

public:
    static const ComponentId COMPONENT_ID;

    Collision(float x, float y)
    : x_{x}, y_{y} {}

    ComponentId get_id() const override {
        return ComponentId::COLLISION;
    }

    virtual Type get_type() const = 0;

    virtual bool is_collided(const Collision& other) = 0;

    bool is_enabled() const { return enabled_; }

    void disable() { enabled_ = false; }

    void enable() { enabled_ = true; }

    virtual ~Collision() {}
};

class CircleCollision: public Collision {
protected:
    float radius_;
    friend class RectangleCollision;

public:
    CircleCollision(float x, float y, float radius)
    : Collision(x, y), radius_{radius} {}

    Type get_type() const override {
        return Type::CIRCLE;
    }

    bool is_collided(const Collision& other) override;
};

class RectangleCollision: public Collision {
protected:
    float width_, height_;
    friend class CircleCollision;

public:
    RectangleCollision(float x, float y, float width, float height)
    : Collision(x, y), width_{width}, height_{height} {}

    Type get_type() const override {
        return Type::RECTANGLE;
    }

    bool is_collided(const Collision& other) override;
};

} // namespace actor
} // namespace tung

#endif