#ifndef LOGIC_GAME_STATE_HPP
#define LOGIC_GAME_STATE_HPP

#include <memory>
#include <graphics/gl/glfw.hpp>
#include <view/abstract/keyboard.hpp>

namespace tung {
namespace state {

class Manager;

// Lớp là base class cho các trạng thái trong game 
class GameState {
protected:
    Manager& manager_;

public:
    // Constructor
    // @manager: Tham chiếu đến lớp quản lý trạng thái 
    GameState(Manager& manager)
    : manager_{manager} {}

    // Hàm sẽ được gọi khi game bắt đầu trạng thái 
    virtual void entry() {}

    // Hàm sẽ được gọi khi game kết thúc trạng thái này 
    virtual void exit() {}

    // Hàm sẽ được gọi khi có một sự kiện chuột 
    // @button: Nút nào được bấm 
    // @type: Các thức bấm 
    // @x, @y: Tọa độ chuột mà sự kiện xảy ra 
    // Return: true nếu đã xử lý sự kiện 
    virtual bool on_mouse_event(MouseButton button, 
            MouseEventType type, float x, float y) 
    {
        return false;
    }

    // Hàm sẽ được gọi khi có một sự kiện bàn phím 
    // @event: Sự kiện bàn phím 
    // Return: true nếu đã xử lý sự kiện 
    virtual bool on_key_event(const KeyEvent& event) { return false; }

    // Destructor
    virtual ~GameState() {}
};

typedef std::unique_ptr<GameState> GameStatePtr;

} // namespace state
} // namespace tung

#endif
