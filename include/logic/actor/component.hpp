#ifndef GAME_LOGIC_ACTOR_COMPONENT_HPP
#define GAME_LOGIC_ACTOR_COMPONENT_HPP

#include <memory>
#include "base.hpp"
#include "component_id.hpp"

namespace tung {
namespace actor {

class Component {
private:
    StrongActorPtr owner_;
    friend class Actor;

public:
    virtual ComponentId get_id() const = 0;

    virtual ~Component() {}

    void set_owner(StrongActorPtr owner) {
        this->owner_ = std::move(owner);
    }
};

} // namespace actor
} // namespace tung

#endif