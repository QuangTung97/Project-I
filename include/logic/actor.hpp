#ifndef GAME_LOGIC_ACTOR_HPP
#define GAME_LOGIC_ACTOR_HPP

#include <memory>
#include <map>

#include "actor_component.hpp"

namespace tung {

class Actor;
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef int ActorId;

class Actor {
private:
    typedef std::map<ActorComponentId, StrongActorComponentPtr> ActorComponents;
    ActorId id_;
    ActorComponents components_;
    friend class ActorFactory;

public:
    ActorId get_id() const {
        return id_;
    }

    template<typename Component>
    std::weak_ptr<Component> get_component(ActorComponentId id) {
        auto find_it = components_.find(id);
        if (find_it != components_.end()) {
            std::shared_ptr<Component> ptr =
                std::dynamic_pointer_cast<Component>(find_it->second);
            return ptr;
        }
        return nullptr;
    }

    void shutdown() {
        // Break circles
        for (auto& e: components_) {
            e.second->set_owner(nullptr);
        }
    }

private:
    void add_component(StrongActorComponentPtr component) {
        ActorComponentId id = component->get_id();
        components_[id] = std::move(component);
    }
};

}

#endif
