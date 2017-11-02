#include <logic/game_logic.hpp>
#include <logic/actor/actor.hpp>
#include <logic/actor/events.hpp>

namespace tung {

GameLogic *GameLogic::this_ = nullptr;

GameLogic::GameLogic(IEventManager& manager) 
: manager_{manager} {
    this_ = this;

    auto listener = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const actor::DestroyEvent&>(event);
        auto it = actors_.find(data.get_id());
        if (it != actors_.end())
            actors_.erase(it);
    };
    actor_destroy_listener_ = listener;

    manager_.add_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
}

GameLogic::~GameLogic() {
    manager_.remove_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
}

} // namespace tung