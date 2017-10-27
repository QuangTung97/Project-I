#include <logic/collision_system.hpp>
#include <logic/actor.hpp>
#include <logic/game_logic.hpp>
#include <logic/collision_component.hpp>

namespace tung {

CollisionSystem::CollisionSystem(IEventManager& manager, ITimer& timer)
: manager_{manager}, timer_{timer} {
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
        const auto& data = dynamic_cast<const ActorDestroyEvent&>(event);
        auto find_it = actor_components_.find(data.get_id());
        if (find_it != actor_components_.end()) {
            auto comp = find_it->second.lock();
            comp->set_owner(nullptr);
            actor_components_.erase(find_it);
        }
    };
    actor_destroy_listener_ = actor_destroy;
    manager_.add_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

void CollisionSystem::update() {
    for (auto i = actor_components_.begin(); 
              i != actor_components_.end(); ++i) {
        auto j = i; ++j;
        for (; j != actor_components_.end(); ++j) {
            auto comp1 = i->second.lock();
            auto comp2 = j->second.lock();
            if (comp1->is_collided(*comp2)) {
                ActorCollideEvent event1{timer_.current_time(), i->first};
                ActorCollideEvent event2{timer_.current_time(), j->first};

                manager_.queue(event1);
                manager_.queue(event2);
            }
        }
    }
}

CollisionSystem::~CollisionSystem() {
    manager_.remove_listener(ACTOR_CREATED, actor_created_listener_);
    manager_.remove_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

} // namespace tung