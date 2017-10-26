#include <logic/position_component.hpp>

namespace tung {

EventType<2010> ACTOR_MOVE;

PositionComponent::PositionComponent(float x, float y)
: x_{x}, y_{y} {}

} // namespace tung