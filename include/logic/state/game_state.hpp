#ifndef LOGIC_GAME_STATE_HPP
#define LOGIC_GAME_STATE_HPP

#include <memory>
#include <graphics/gl/glfw.hpp>

namespace tung {
namespace state {

class Manager;

class GameState {
protected:
    Manager& manager_;

public:
    GameState(Manager& manager)
    : manager_{manager} {}

    virtual void entry() {}

    virtual void exit() {}

    virtual bool on_mouse_event(
        MouseButton button, 
        MouseEventType type, 
        float x, float y) 
    {
        return false;
    }

    virtual ~GameState() {}
};

typedef std::unique_ptr<GameState> GameStatePtr;

} // namespace state
} // namespace tung

#endif