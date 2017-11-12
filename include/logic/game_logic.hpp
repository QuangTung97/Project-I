#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <unordered_map>
#include "actor/actor.hpp"
#include <logic/abstract/event_manager.hpp>
#include <cassert>

namespace tung {

using actor::ActorId;
using actor::StrongActorPtr;
using actor::WeakActorPtr;

// Control all actors for the game
class GameLogic {
private:
    typedef std::unordered_map<ActorId, StrongActorPtr> Actors;
    Actors actors_;
    IEventManager& manager_;
    EventListener actor_destroy_listener_;

    static GameLogic *this_;

public:
    GameLogic(IEventManager& manager);

    static GameLogic& get() {
        return *this_;
    }

    WeakActorPtr get_actor(ActorId id) {
        auto it = actors_.find(id);
        assert (it != actors_.end());
        return it->second;
    }

    void add_actor(StrongActorPtr actor) {
        actors_[actor->get_id()] = std::move(actor);
    }

    int get_actor_count() {
        return actors_.size();
    }

    ~GameLogic();
};

} // namespace tung

#endif