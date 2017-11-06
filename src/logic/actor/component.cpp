#include <logic/actor/component.hpp>
#include <logic/actor/actor.hpp>

namespace tung {
namespace actor {

void Component::set_owner(StrongActorPtr owner) {
    this->owner_ = std::move(owner);
}

ActorId Component::get_actor_id() const {
    return owner_->get_id();
}

} // namespace actor
} // namespace tung