#ifndef GAME_LOGIC_ACTOR_HPP
#define GAME_LOGIC_ACTOR_HPP

#include <memory>
#include <map>

#include <logic/basic/event.hpp>
#include "base.hpp"
#include "component_id.hpp"

namespace tung {
namespace actor {

class IdGenerator {
private:
    static ActorId last_;

public:
    static ActorId new_id();
};

// Actor Events
extern EventType<9000> EVENT_DESTROY;
extern EventType<9001> EVENT_CREATED;
extern EventType<9002> EVENT_MOVE;

class DestroyEvent: public EventData {
private:
    const ActorId id_;

public:
    DestroyEvent(TimePoint time_point, ActorId id)
    : EventData(time_point, EVENT_DESTROY), id_{id} {}

    ActorId get_id() const { return id_; }

    IEventDataPtr clone() const override {
        return std::make_unique<DestroyEvent>(time_point_, id_);
    }

    virtual ~DestroyEvent() {}
};

class CreatedEvent: public EventData {
private:
    const ActorId id_;

public:
    CreatedEvent(TimePoint time_point, ActorId id)
    : EventData(time_point, EVENT_CREATED), id_{id} {}

    ActorId get_id() const { return id_; }

    IEventDataPtr clone() const override {
        return std::make_unique<CreatedEvent>(time_point_, id_);
    }

    virtual ~CreatedEvent() {}
};

class MoveEvent: public EventData {
private:
    const ActorId id_;
    const float x_, y_;

public:
    MoveEvent(TimePoint time_point, ActorId id,
        float x, float y)
    : EventData{time_point, EVENT_MOVE}, id_{id}, x_{x}, y_{y} {}

    ActorId get_id() const {
        return id_;
    }

    float get_x() const { return x_; }

    float get_y() const { return y_; }

    IEventDataPtr clone() const override {
        return std::make_unique<MoveEvent>(time_point_, id_, x_, y_);
    }
};

class Actor {
private:
    typedef std::map<ComponentId, StrongComponentPtr> ActorComponents;
    ActorId id_;
    ActorComponents components_;
    friend class ActorFactory;

public:
    Actor(ActorId id): id_{id} {}

    ActorId get_id() const {
        return id_;
    }

    template<typename Component_>
    std::weak_ptr<Component_> get_component(ComponentId id) {
        std::shared_ptr<Component_> ptr = nullptr;
        auto find_it = components_.find(id);
        if (find_it != components_.end()) {
            ptr = std::dynamic_pointer_cast<Component_>(find_it->second);
        }
        return ptr;
    }

    template<typename Component_>
    std::weak_ptr<Component_> get_component() {
        std::shared_ptr<Component_> ptr = nullptr;
        auto find_it = components_.find(Component_::COMPONENT_ID);
        if (find_it != components_.end()) {
            ptr = std::dynamic_pointer_cast<Component_>(find_it->second);
        }
        return ptr;
    }

public:
    void add_component(StrongComponentPtr component);
};

} // namespace actor
} // namespace tung

#endif
