#ifndef LOGIC_GAME_BOMB_HPP
#define LOGIC_GAME_BOMB_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>

namespace tung {
namespace game {

// Lớp đại diện cho bomb 
class Bomb: public actor::Actor {
private:
    friend class BombFlyProcess;
    friend class FlyProcess;

    state::Manager& state_manager_;
    float x_, y_;
    const float velocity_ = 0.7f;
    const float height_ = 0.15f;
    bool flying_ = false;
    StrongProcessPtr fly_process_;

public:
    // Constructor
    // @state_manager: Tham chiếu đến class quản lý trạng thái của game 
    // @x, @y: Tọa độ bắt đầu của quả bomb 
    Bomb(state::Manager& state_manager, float x, float y);

    // Được gọi ngay sau constructor, để khởi tạo quả bomb
    // Cần phải tạo ra một hàm init riêng bởi vì để sử dụng 
    // được enable_shared_from_this
    void init();

    // Bomb bắt đầu rơi 
    void start_fly();

    // Xoay quả bomb đi một góc
    void rotate(float degree);

    // Trả về true nếu đang rơi  
    bool flying() { return flying_; }

    // Kết thúc rơi 
    void end_fly();

    // Phát nổ 
    void explode();
};

} // namespace game
} // namespace tung
#endif 
