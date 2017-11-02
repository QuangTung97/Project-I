#include <logic/actor/collision.hpp>

namespace tung {
namespace actor {

EventType<7001> EVENT_COLLIDE;

const ComponentId Collision::COMPONENT_ID = ComponentId::COLLISION;

bool CircleCollision::is_collided(const Collision& other) {
    if (other.get_type() == Type::CIRCLE) {
        const auto& circle = dynamic_cast<const CircleCollision&>(other);
        float dx = circle.x_ - this->x_;
        float dy = circle.y_ - this->y_;
        float d2 = dx * dx + dy * dy;
        float radius2 = circle.radius_ + this->radius_;
        radius2 *= radius2;
        if (radius2 < d2)
            return false;
        else
            return true;
    }
    return false;
}

} // namespace actor
} // namespace tung