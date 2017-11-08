#ifndef LOGIC_STATE_START_STATE_HPP
#define LOGIC_STATE_START_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <memory>

namespace tung {
namespace state {

class StartState: public GameState {
protected:
    IDrawablePtr background_;

public:
    StartState(Manager& manager);

    void entry() override;

    void exit() override;

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y) override;
};

} // namespace state
} // namespace tung

#endif