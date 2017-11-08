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

class Actor: public std::enable_shared_from_this<Actor> {
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

    virtual ~Actor() {}

public:
    void add_component(StrongComponentPtr component);
};

} // namespace actor
} // namespace tung

#endif
