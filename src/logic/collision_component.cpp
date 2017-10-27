#include <logic/collision_component.hpp>

namespace tung {

EventType<7001> ACTOR_COLLIDE;

bool CircleCollisionComponent::is_collided(const CollisionComponent& other) {
    if (other.get_type() == Type::CIRCLE) {
        const auto& circle = dynamic_cast<const CircleCollisionComponent&>(other);
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

} // namespace tung