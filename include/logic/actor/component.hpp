#ifndef GAME_LOGIC_ACTOR_COMPONENT_HPP
#define GAME_LOGIC_ACTOR_COMPONENT_HPP

#include <memory>
#include "base.hpp"
#include "component_id.hpp"

namespace tung {
namespace actor {

class Component: public std::enable_shared_from_this<Component> {
private:
    StrongActorPtr owner_;
    friend class Actor;

public:
    virtual ComponentId get_id() const = 0;

    virtual ~Component() {}

    void set_owner(StrongActorPtr owner);

    ActorId get_actor_id() const;
};

} // namespace actor
} // namespace tung

#endif