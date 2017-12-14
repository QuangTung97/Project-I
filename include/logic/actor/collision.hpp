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

// Kiểm tra liệu rằng một hình chữ nhật với một hình trong có chồng lên nhau hay không 
// @rx, @ry: Tọa độ tâm của hình chữ nhật
// @width, @height: Chiều rộng và chiều cao của hình chữ nhật. 
// @cx, @cy: Tọa độ tâm hình tròn 
// @radius: bán kính hình tròng
// Return: true nếu như chúng chồng lên nhau
bool is_rectangle_circle_collided(float rx, float ry, 
    float width, float height, 
    float cx, float cy, float radius);

// Kiểm tra liệu rằng hai hình chữ nhật có chồng lên nhau hay không 
// @rx, @ry: Tọa độ tâm của hình chữ nhật
// @width, @height: Chiều rộng và chiều cao của hình chữ nhật. 
// Return: true nếu như chúng chồng lên nhau 
bool is_two_rectangle_collided(
    float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2);

// Class chứa thông tin va chạm của actor 
class Collision: public Component {
protected:
    float x_, y_;
    // Kiểu của object 
    enum class Type {
        CIRCLE, // Hình tròn 
        RECTANGLE // Hình chữ nhật 
    };
    friend class tung::system::Collision;
    bool enabled_ = true;

public:
    static const ComponentId COMPONENT_ID;

    // Constructor 
    // @x: Tọa độ theo x.
    // @y: Tọa độ theo y. 
    Collision(float x, float y)
    : x_{x}, y_{y} {}

    ComponentId get_id() const override {
        return ComponentId::COLLISION;
    }

    // Trả về kiểu của object 
    virtual Type get_type() const = 0;

    // Kiểm tra xem nó có va chạm với một actor khác không 
    // (thông qua thành phần Collision của actor đấy )
    virtual bool is_collided(const Collision& other) = 0;

    // Enable: Khi một thành phần collision bị disable, nó sẽ không thể 
    // va đập với thành phần khác 

    // Kiểm tra xem có enable hay không 
    bool is_enabled() const { return enabled_; }

    // Disable thành phần này 
    void disable() { enabled_ = false; }

    // Enable thành phần này. 
    void enable() { enabled_ = true; }

    // Destructor
    virtual ~Collision() {}
};

// Thành phần collision trong trường hợp là hình tròn 
class CircleCollision: public Collision {
protected:
    float radius_;
    friend class RectangleCollision;

public:
    // Constructor
    // @x, @y: Tọa độ tâm hình tròn 
    // @radius: Bán kính hình tròn.
    CircleCollision(float x, float y, float radius)
    : Collision(x, y), radius_{radius} {}

    Type get_type() const override {
        return Type::CIRCLE;
    }

    bool is_collided(const Collision& other) override;
};

// Thành phần collision trong trường hợp là hình chữ nhật 
class RectangleCollision: public Collision {
protected:
    float width_, height_;
    friend class CircleCollision;

public:
    // Constructor
    // @x, @y: Tọa độ tâm hình chữ nhật 
    // @width, @height: Chiều rộng và chiều cao hình chữ nhật. 
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