#ifndef LOGIC_GAME_BULLET_HPP
#define LOGIC_GAME_BULLET_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>
#include <logic/abstract/process.hpp>

namespace tung {
namespace game {

class Bullet: public actor::Actor {
private:
    friend class BulletFlyProcess;

    state::Manager& state_manager_;
    float x_, y_;
    const float velocity_ = 2.4f;
    float vx_, vy_;
    StrongProcessPtr fly_process_;

public:
    Bullet(state::Manager& state_manager, 
        float x, float y, float degree);

    void init();

    void start_fly();

    void end_fly();
};

} // namespace game
} // namespace tung

#endif