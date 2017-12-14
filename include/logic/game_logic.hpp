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
// Điều khiển tất cả các actor trong game 
class GameLogic {
private:
    typedef std::unordered_map<ActorId, StrongActorPtr> Actors;
    Actors actors_;
    IEventManager& manager_;
    EventListener actor_destroy_listener_;

    static GameLogic *this_;

public:
    // Constructor
    // @manager: Manager quản lý sự kiện của hệ thống. 
    GameLogic(IEventManager& manager);

    // Trả về con trỏ đến object duy nhất của class này. 
    static GameLogic& get() {
        return *this_;
    }

    // Trả về con trỏ trỏ đến actor 
    // @id: Id của actor 
    WeakActorPtr get_actor(ActorId id) {
        auto it = actors_.find(id);
        assert (it != actors_.end());
        return it->second;
    }

    // Thêm một actor vào từ điển các actor
    // @actor: Con trỏ đến actor 
    void add_actor(StrongActorPtr actor) {
        actors_[actor->get_id()] = std::move(actor);
    }

    // Trả về số lượng các actor trong hệ thống 
    int get_actor_count() {
        return actors_.size();
    }

    ~GameLogic();
};

} // namespace tung

#endif