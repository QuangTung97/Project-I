#include <logic/collision_component.hpp>

namespace tung {

CollisionComponent::CollisionComponent(float x, float y, float radius)
: x_{x}, y_{y}, radius_{radius} {
}

CollisionComponent::~CollisionComponent() {

}

} // namespace tung