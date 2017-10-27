#ifndef LOGIC_COLLISION_COMPONENT_HPP
#define LOGIC_COLLISION_COMPONENT_HPP

#include "actor_component.hpp"

namespace tung {

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