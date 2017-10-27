#include <logic/game_logic.hpp>
#include <logic/actor.hpp>

namespace tung {

GameLogic::GameLogic(IEventManager& manager) 
: manager_{manager} {
    auto listener = [this](const IEventData& event) {
        const auto& data = dynamic_cast<const ActorDestroyEvent&>(event);
        auto it = actors_.find(data.get_id());
        actors_.erase(it);
    };
    actor_destroy_listener_ = listener;

    manager_.add_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

GameLogic::~GameLogic() {
    manager_.remove_listener(ACTOR_DESTROY, actor_destroy_listener_);
}

} // namespace tung