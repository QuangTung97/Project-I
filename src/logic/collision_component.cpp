#include <logic/collision_component.hpp>

namespace tung {

EventType<7000> ACTORS_COLLIDE;

CollisionComponent::CollisionComponent(float x, float y, float radius)
: x_{x}, y_{y}, radius_{radius} {
}

CollisionComponent::~CollisionComponent() {

}

} // namespace tung