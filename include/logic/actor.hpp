#ifndef GAME_LOGIC_ACTOR_HPP
#define GAME_LOGIC_ACTOR_HPP

#include <memory>
#include <map>

#include "actor_component.hpp"
#include <logic/event.hpp>

namespace tung {

class Actor;
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef int ActorId;

extern EventType<9000> ACTOR_DESTROY;

class ActorDestroyEvent: public EventData {
private:
    ActorId id_;

public:
    ActorDestroyEvent(TimePoint time_point, ActorId id)
    : EventData(time_point, ACTOR_DESTROY), id_{id} {}

    ActorId get_id() const { return id_; }

    virtual ~ActorDestroyEvent() {}
};

class Actor {
private:
    typedef std::map<ActorComponentId, StrongActorComponentPtr> ActorComponents;
    ActorId id_;
    ActorComponents components_;
    friend class ActorFactory;

public:
    Actor(ActorId id): id_{id} {}

    ActorId get_id() const {
        return id_;
    }

    template<typename Component>
    std::weak_ptr<Component> get_component(ActorComponentId id) {
        std::shared_ptr<Component> ptr = nullptr;
        auto find_it = components_.find(id);
        if (find_it != components_.end()) {
            ptr = std::dynamic_pointer_cast<Component>(find_it->second);
        }
        return ptr;
    }

    void shutdown() {
        // Break circles
        for (auto& e: components_) {
            e.second->set_owner(nullptr);
        }
    }

public:
    void add_component(StrongActorComponentPtr component) {
        ActorComponentId id = component->get_id();
        components_[id] = std::move(component);
    }
};

}

#endif
