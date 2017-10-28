#include <logic/actor.hpp>

namespace tung {

EventType<9000> ACTOR_DESTROY;
EventType<9001> ACTOR_CREATED;
EventType<9002> ACTOR_MOVE;

ActorId ActorIdGenerator::last_ = 0;

ActorId ActorIdGenerator::new_id() {
    return ++last_;
}

} // namespace tung