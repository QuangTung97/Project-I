#include <logic/actor.hpp>

namespace tung {

EventType<9000> ACTOR_DESTROY;
EventType<9000> ACTOR_CREATED;

ActorId ActorIdGenerator::last_ = 0;

ActorId ActorIdGenerator::new_id() {
    return ++last_;
}

} // namespace tung