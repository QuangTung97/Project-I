#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <unordered_map>
#include "actor/actor.hpp"
#include <logic/abstract/event_manager.hpp>

namespace tung {

using actor::ActorId;
using actor::StrongActorPtr;
using actor::WeakActorPtr;

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
        return actors_[id];
    }

    void add_actor(StrongActorPtr actor) {
        actors_[actor->get_id()] = std::move(actor);
    }

    ~GameLogic();
};

} // namespace tung

#endif