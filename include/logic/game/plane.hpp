#ifndef LOGIC_GAME_PLANE_HPP
#define LOGIC_GAME_PLANE_HPP

#include <logic/actor/actor.hpp>
#include <logic/abstract/process.hpp>
#include <logic/game/manager.hpp>
#include <vector>
#include <random>

namespace tung {
namespace game {

class Plane;

class FlyProcess: public Process {
private:
    Plane& plane_;

public:
    FlyProcess(Plane& plane): plane_{plane} {}

protected:
    void on_init() override;

    void on_update(milliseconds dt) override;

    void on_success() override;

    void on_fail() override;

    void on_abort() override;
};

class Plane: public actor::Actor {
private:
    friend class FlyProcess;

    state::Manager& state_manager_;
    float x_, y_;
    float dx_ = 0.0f;
    const float velocity_ = 0.8;
    const bool is_fighter_ = true;
    const float max_distance_ = 4;

    StrongProcessPtr fly_process_;
    StrongProcessPtr destroy_plane_;

public:
    Plane(state::Manager& state_manager, bool is_fighter);

    void init();

    void start_fly();

    bool is_fighter() { return is_fighter_; }

    void end_fly();

    void explode();
};

} // namespace game
} // namespace tung

#endif