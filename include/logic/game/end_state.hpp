#ifndef LOGIC_STATE_END_STATE_HPP
#define LOGIC_STATE_END_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <memory>

namespace tung {
namespace state {

// Trạng thái sau trạng thái đang chơi (playing)
// Hiện tại chưa được sử dụng 
class EndState: public GameState {
private:
    IDrawablePtr background_;

public:
    EndState(Manager& manager);

    void entry() override;

    void exit() override;

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y) override;
};

} // namespace state
} // namespace tung

#endif
