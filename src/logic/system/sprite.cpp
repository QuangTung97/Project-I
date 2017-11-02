#include <logic/system/sprite.hpp>
#include <logic/actor/actor.hpp>
#include <logic/game_logic.hpp>

namespace tung {
namespace system {

Sprite::Sprite(IEventManager& manager, ITimer& timer) 
: manager_{manager}, timer_{timer} 
{
    auto actor_created = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::CreatedEvent&>(event_);

        auto tmp_actor = GameLogic::get().get_actor(event.get_id()).lock();
        if (tmp_actor == nullptr) 
            return;

        components_[event.get_id()] = tmp_actor->get_component<actor::Sprite>();
    };

    auto actor_destroy = [this](const IEventData& event) {

    };

    auto actor_move = [this](const IEventData& event) {

    };

    auto sprite_started = [this](const IEventData& event) {

    };

    auto sprite_ended = [this](const IEventData& event) {
        
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