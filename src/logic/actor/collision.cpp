#include <logic/actor/collision.hpp>

namespace tung {
namespace actor {

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

bool is_inside_circle(float cx, float cy, float radius, float x, float y) {
    float dx = x - cx;
    float dy = y - cy;
    float d2 = dx * dx + dy * dy;
    if (d2 <= radius * radius)
        return true;
    else
        return false;
}

bool is_two_circle_collided(float x1, float y1, float radius1,
    float x2, float y2, float radius2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float d2 = dx * dx + dy * dy;
    float sum = radius1 + radius2;
    return d2 < sum * sum;
}

bool is_rectangle_circle_collided(float rx, float ry, 
    float width, float height, 
    float cx, float cy, float radius) 
{
    float dx = cx - rx;
    float dy = cy - ry;
    unsigned int flags = 0;
    flags |= std::abs(dx) > width / 2;
    flags |= (std::abs(dy) > height / 2) << 1;
    if (flags == 0b11) {
        // Corner coordinates
        float x = rx + sign(dx) * width / 2;
        float y = ry + sign(dy) * height / 2;
        return is_inside_circle(cx, cy, radius, x, y);
    }
    else if (flags == 0b01) {
        return std::abs(dx) <= width / 2 + radius;
    }
    else if (flags == 0b10) {
        return std::abs(dy) <= height / 2 + radius;
    }
    else {
        return true;
    }
}

bool is_two_rectangle_collided(
    float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    unsigned int flags = 0;
    flags |= std::abs(dx) <= (width1 + width2) / 2;
    flags |= (std::abs(dy) <= (height1 + height2) / 2) << 1;
    return flags == 0b11;
}

const ComponentId Collision::COMPONENT_ID = ComponentId::COLLISION;

bool CircleCollision::is_collided(const Collision& other) {
    if (other.get_type() == Type::CIRCLE) {
        const auto& circle = dynamic_cast<const CircleCollision&>(other);
        return is_two_circle_collided(
            x_, y_, radius_,
            circle.x_, circle.y_, circle.radius_
        );
    }
    else if (other.get_type() == Type::RECTANGLE) {
        const auto& rec = dynamic_cast<const RectangleCollision&>(other);
        return is_rectangle_circle_collided(
            rec.x_, rec.y_, rec.width_, rec.height_,
            x_, y_, radius_
        );
    }
    return false;
}

bool RectangleCollision::is_collided(const Collision& other) {
    if (other.get_type() == Type::CIRCLE) {
        const auto& circle = dynamic_cast<const CircleCollision&>(other);
        return is_rectangle_circle_collided(
            x_, y_, width_, height_,
            circle.x_, circle.y_, circle.radius_
        );
    }
    else if (other.get_type() == Type::RECTANGLE) {
        const auto& rec = dynamic_cast<const RectangleCollision&>(other);
        return is_two_rectangle_collided(
            x_, y_, width_, height_,
            rec.x_, rec.y_, rec.width_, rec.width_
        );
    }
    return false;
}

} // namespace actor
} // namespace tung