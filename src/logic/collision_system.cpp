#include <logic/collision_system.hpp>
#include <logic/actor.hpp>
#include <logic/game_logic.hpp>
#include <logic/collision_component.hpp>

namespace tung {

CollisionSystem::CollisionSystem(IEventManager& manager)
: manager_{manager} {
    auto actor_created = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const ActorCreatedEvent&>(event);
        auto actor = GameLogic::get().get_actor(data.get_id()).lock();
        if (actor) {
            actor_components_[data.get_id()] = 
                actor->get_component<CollisionComponent>(ActorComponentId::COLLISION);
        }
    };
    actor_created_listener_ = actor_created;
    manager_.add_listener(ACTOR_CREATED, actor_created_listener_);

    auto actor_destroy = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const ActorCreatedEvent&>(event);
        auto find_it = actor_components_.find(data.get_id());
        if (find_it != actor_components_.end())
            actor_components_.erase(find_it);
    };
    actor_destroy_listener_ = actor_destroy;
    manager_.add_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

void CollisionSystem::update() {

}

CollisionSystem::~CollisionSystem() {
    manager_.remove_listener(ACTOR_CREATED, actor_created_listener_);
    manager_.remove_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

} // namespace tung