#include <logic/actor/actor.hpp>
#include <logic/actor/component.hpp>

namespace tung {
namespace actor {

EventType<9000> EVENT_DESTROY;
EventType<9001> EVENT_CREATED;
EventType<9002> EVENT_MOVE;

ActorId IdGenerator::last_ = 0;

ActorId IdGenerator::new_id() {
    return ++last_;
}

void Actor::add_component(StrongComponentPtr component) {
    ComponentId id = component->get_id();
    components_[id] = std::move(component);
}

} // namespace actor
} // namespace tung