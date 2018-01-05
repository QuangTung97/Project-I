#ifndef LOGIC_GAME_CANNON_HPP
#define LOGIC_GAME_CANNON_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>

namespace tung {
namespace game {

// Lớp đại diện cho khẩu súng 
class Cannon: public actor::Actor {
private:
    state::Manager& state_manager_;
    actor::ActorId base_id_, head_id_;
    float head_angle_;

public:
    // Constructor
    // @state_manager: Tham chiếu đến lớp quản lý trạng thái 
    Cannon(state::Manager& state_manager)
    : actor::Actor{actor::IdGenerator::new_id()},
        state_manager_{state_manager}
    {}

    // Khởi tạo khẩu súng 
    void init();

    // Quay khẩu súng một góc @degree tính theo độ 
    void rotate(float degree);

    // Trả về góc hiện tại của khẩu súng 
    float angle() const { return head_angle_; }

    // Bắn
    // Return: ActorId của viên đạn 
    actor::ActorId shot();

    // Destructor
    ~Cannon();
};

} // namespace game
} // namespace tung

#endif
