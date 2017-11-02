#include <logic/system/sprite.hpp>
#include <logic/actor/actor.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/events.hpp>

namespace tung {
namespace system {

Sprite::Sprite(IEventManager& manager) 
: manager_{manager}
{
    auto actor_created = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::CreatedEvent&>(event_);

        auto tmp_actor = GameLogic::get().get_actor(event.get_id()).lock();
        if (tmp_actor) {
            components_[event.get_id()] = tmp_actor->get_component<actor::Sprite>();
        }
    };

    auto actor_destroy = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::DestroyEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->set_owner(nullptr);
            components_.erase(find_it);
        }
    };

    auto actor_move = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::MoveEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->move_to(event.get_x(), event.get_y());
        }
    };

    auto sprite_started = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::SpriteStartedEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->start(event.get_index());
        }
    };

    auto sprite_ended = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::SpriteEndedEvent&>(event_);
        auto find_it = components_.find(event.get_id());
        if (find_it != components_.end()) {
            auto comp = find_it->second.lock();
            comp->end(event.get_index());
        }
    };

    actor_created_listener_ = actor_created;
    actor_destroy_listener_ = actor_destroy;
    actor_move_listener_ = actor_move;
    sprite_started_listener_ = sprite_started;
    sprite_ended_listener_ = sprite_ended;

    manager_.add_listener(actor::EVENT_CREATED, actor_created_listener_);
    manager_.add_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    manager_.add_listener(actor::EVENT_MOVE, actor_move_listener_);
    manager_.add_listener(actor::EVENT_SPRITE_STARTED, sprite_started_listener_);
    manager_.add_listener(actor::EVENT_SPRITE_ENDED, sprite_ended_listener_);
}

Sprite::~Sprite() {
    manager_.remove_listener(actor::EVENT_SPRITE_ENDED, sprite_ended_listener_);
    manager_.remove_listener(actor::EVENT_SPRITE_STARTED, sprite_started_listener_);
    manager_.remove_listener(actor::EVENT_MOVE, actor_move_listener_);
    manager_.remove_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    manager_.remove_listener(actor::EVENT_CREATED, actor_created_listener_);
}


} // namespace system
} // namespace tung