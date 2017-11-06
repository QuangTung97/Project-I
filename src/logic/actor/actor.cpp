#include <logic/actor/actor.hpp>
#include <logic/actor/component.hpp>

namespace tung {
namespace actor {

ActorId IdGenerator::last_ = 0;

ActorId IdGenerator::new_id() {
    return ++last_;
}

void Actor::add_component(StrongComponentPtr component) {
    ComponentId id = component->get_id();
    component->set_owner(shared_from_this());
    components_[id] = std::move(component);
}

} // namespace actor
} // namespace tung