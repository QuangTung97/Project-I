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

class Plane: public actor::Actor {
private:
    friend class FlyProcess;

    state::Manager& state_manager_;
    state::PlayingState& playing_state_;
    float x_, y_;
    float dx_ = 0.0f;
    const float base_velocity_ = 0.8f;
    const float velocity_;
    bool is_fighter_ = true;
    const float max_distance_ = 4;

    float drop_bomb_x_position_;

    StrongProcessPtr fly_process_;
    StrongProcessPtr destroy_plane_;

public:
    Plane(state::Manager& state_manager, 
        float scaling_velocity, state::PlayingState& playing_state);

    void init();

    void start_fly();

    bool is_fighter() { return is_fighter_; }

    void end_fly();

    void explode();

    virtual ~Plane();
};

} // namespace game
} // namespace tung

#endif