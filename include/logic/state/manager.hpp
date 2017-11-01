#ifndef GAME_LOGIC_STATE_MANAGER_HPP
#define GAME_LOGIC_STATE_MANAGER_HPP

#include "game_state.hpp"
#include <graphics/abstract/drawable.hpp>
#include <logic/abstract/event_manager.hpp>

namespace tung {
namespace state {

class Manager {
private:
    friend class GameState;
    GameState *current_;

    GameStatePtr start_;
    GameStatePtr playing_;
    GameStatePtr end_;

private:
    IEventManager& event_manager_;
    IDrawableManager& root_drawable_;

public:
    Manager(IEventManager& manager, IDrawableManager& root_drawable);

    void make_transition_to(GameState& state);

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y);

    IEventManager& get_event_manager() const {
        return event_manager_;
    }

    IDrawableManager& root() const {
        return root_drawable_;
    }
};

}
} // namespace tung

#endif