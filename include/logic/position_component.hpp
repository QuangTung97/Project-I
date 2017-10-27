#ifndef LOGIC_POSITION_COMPONENT_HPP
#define LOGIC_POSITION_COMPONENT_HPP

#include "actor_component.hpp"
#include <logic/event.hpp>
#include <logic/abstract/event_manager.hpp>

namespace tung {

typedef int ActorId;
extern EventType<2010> ACTOR_MOVE;

class ActorMoveEvent: public EventData {
private:
    ActorId id_;
    float x_, y_;

public:
    ActorMoveEvent(TimePoint time_point, ActorId id,
        float x, float y)
    : EventData{time_point, ACTOR_MOVE}, id_{id}, x_{x}, y_{y} {}

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