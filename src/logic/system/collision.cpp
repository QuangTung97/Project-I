#include <logic/system/collision.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/events.hpp>

#include <iostream>

namespace tung {
namespace system {

Collision::Collision(IEventManager& manager, ITimer& timer)
: manager_{manager}, timer_{timer} {
    auto actor_created = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const actor::CreatedEvent&>(event);
        auto actor = GameLogic::get().get_actor(data.get_id()).lock();
        if (actor) {
            auto comp = actor->get_component<actor::Collision>().lock();
            if (comp)
                actor_components_[data.get_id()] = comp;
        }
    };
    actor_created_listener_ = actor_created;
    manager_.add_listener(actor::EVENT_CREATED, actor_created_listener_);

    auto actor_destroy = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const actor::DestroyEvent&>(event);
        auto find_it = actor_components_.find(data.get_id());
        if (find_it != actor_components_.end()) {
            auto comp = find_it->second.lock();
            comp->set_owner(nullptr);
            actor_components_.erase(find_it);
        }
    };
    actor_destroy_listener_ = actor_destroy;
    manager_.add_listener(actor::EVENT_DESTROY, actor_destroy_listener_);

    auto actor_move = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const actor::MoveEvent&>(event);
        auto find_it = actor_components_.find(data.get_id());
        if (find_it != actor_components_.end()) {
            auto comp = find_it->second.lock();
            comp->x_ = data.get_x();
            comp->y_ = data.get_y();
        }
    };
    actor_move_listener_ = actor_move;
    manager_.add_listener(actor::EVENT_MOVE, actor_move_listener_);
}

void Collision::update() {
    for (auto i = actor_components_.begin(); 
              i != actor_components_.end(); ++i) {
        auto j = i; ++j;
        for (; j != actor_components_.end(); ++j) {
            auto comp1 = i->second.lock();
            auto comp2 = j->second.lock();
            if (comp1->is_collided(*comp2)) {
                actor::CollideEvent event1{timer_.current_time(), i->first};
                actor::CollideEvent event2{timer_.current_time(), j->first};

                manager_.queue(event1);
                manager_.queue(event2);
            }
        }
    }
}

Collision::~Collision() {
    manager_.remove_listener(actor::EVENT_CREATED, actor_created_listener_);
    manager_.remove_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    manager_.remove_listener(actor::EVENT_MOVE, actor_move_listener_);
}

} // namespace system
} // namespace tung