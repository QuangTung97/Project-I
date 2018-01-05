#ifndef LOGIC_GAME_BOMB_HPP
#define LOGIC_GAME_BOMB_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>

namespace tung {
namespace game {

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
    Bomb(state::Manager& state_manager, float x, float y);

    void init();

    void start_fly();

    void rotate(float degree);

    bool flying() { return flying_; }

    void end_fly();

    void explode();
};

} // namespace game
} // namespace tung
#endif 
