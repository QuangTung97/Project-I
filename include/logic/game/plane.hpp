#ifndef LOGIC_GAME_PLANE_HPP
#define LOGIC_GAME_PLANE_HPP

#include <logic/actor/actor.hpp>
#include <logic/abstract/process.hpp>
#include <logic/game/manager.hpp>
#include <vector>
#include <random>

namespace tung {

namespace state {
class PlayingState;
}

namespace game {

// Lớp đại diện cho một máy bay 
class Plane: public actor::Actor {
private:
    friend class FlyProcess;

    state::Manager& state_manager_;
    state::PlayingState& playing_state_;
    float x_, y_;
    const float base_velocity_ = 0.8f;
    const float velocity_;
    bool is_fighter_ = true;
    const float max_distance_ = 4;

    float drop_bomb_x_position_;
    bool will_drop_bomb_ = false;

    StrongProcessPtr fly_process_;
    StrongProcessPtr destroy_plane_;

public:
    // Constructor
    // @state_manager: Tham chiếu đến bộ quản lý trạng thái 
    // @scaling_velocity: Tỉ lệ vận tốc 
    // @playings_state: Tham chiếu đến object thái đang chơi 
    Plane(state::Manager& state_manager, 
        float scaling_velocity, state::PlayingState& playing_state);

    // Khởi tạo 
    void init();

    // Bắt đầu bay 
    void start_fly();

    // Trả về liệu máy bay có phải là máy bay chiến đấu hay không 
    bool is_fighter() { return is_fighter_; }

    // Kết thúc bay 
    void end_fly();

    // Phát nổ 
    void explode();

    // Destructor
    virtual ~Plane();
};

} // namespace game
} // namespace tung

#endif
