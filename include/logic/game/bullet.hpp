#ifndef LOGIC_GAME_BULLET_HPP
#define LOGIC_GAME_BULLET_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>
#include <logic/abstract/process.hpp>

namespace tung {
namespace game {

// Lớp đại diện cho một viên đạn 
class Bullet: public actor::Actor {
private:
    friend class BulletFlyProcess;

    state::Manager& state_manager_;
    float x_, y_;
    const float velocity_ = 2.4f;
    float vx_, vy_;
    StrongProcessPtr fly_process_;

public:
    // Constructor
    // @state_manager: Tham chiếu đến class trạng thái của game 
    // @x, @y: Tọa độ ban đầu của viên đạn 
    // @degree: Góc bay của viên đạn 
    Bullet(state::Manager& state_manager, 
        float x, float y, float degree);

    // Khởi tạo viên đạn 
    void init();

    // Bắt đầu bay 
    void start_fly();

    // Kết thúc bay 
    void end_fly();

    // Destructor
    virtual ~Bullet();
};

} // namespace game
} // namespace tung

#endif
