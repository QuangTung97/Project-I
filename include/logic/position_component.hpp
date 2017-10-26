#ifndef LOGIC_POSITION_COMPONENT_HPP
#define LOGIC_POSITION_COMPONENT_HPP

#include "actor_component.hpp"
#include <logic/event.hpp>
#include <logic/abstract/event_manager.hpp>

namespace tung {

extern EventType<2010> ACTOR_MOVE;

class ActorMoveEvent: public EventData {
private:
    float x_, y_;

public:
    ActorMoveEvent(TimePoint time_point, float x, float y)
        : EventData{time_point, ACTOR_MOVE}, x_{x}, y_{y} {}

    float get_x() const { return x_; }

    float get_y() const { return y_; }
};

class PositionComponent: public ActorComponent {
private:
    float x_, y_;

public:
    PositionComponent(float x, float y);

    ActorComponentId get_id() const override {
        return ActorComponentId::POSITION;
    }

    virtual ~PositionComponent() {}
};

} // namespace tung

#endif