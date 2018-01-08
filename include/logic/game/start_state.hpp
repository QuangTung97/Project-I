#ifndef LOGIC_STATE_START_STATE_HPP
#define LOGIC_STATE_START_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <memory>

namespace tung {
namespace state {

// Class đại diện cho trạng thái bắt đầu chơi 
// Chỉ có một object của class này trong game 
class StartState: public GameState {
protected:
    IDrawablePtr background_;

public:
    // Constructor
    // @manager: Tham chiếu đến bộ quản lý trạng thái 
    StartState(Manager& manager);

    void entry() override;

    void exit() override;

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y) override;

    bool on_key_event(const KeyEvent&) override;
};

} // namespace state
} // namespace tung

#endif
