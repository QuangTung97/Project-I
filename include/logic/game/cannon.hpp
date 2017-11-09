#ifndef LOGIC_GAME_CANNON_HPP
#define LOGIC_GAME_CANNON_HPP

#include <logic/actor/actor.hpp>
#include <logic/game/manager.hpp>

namespace tung {
namespace game {

class Cannon: public actor::Actor {
private:
    state::Manager& state_manager_;
    actor::ActorId base_id_, head_id_;
    float head_angle_;

public:
    Cannon(state::Manager& state_manager)
    : actor::Actor{actor::IdGenerator::new_id()},
        state_manager_{state_manager}
    {}

    void init();

    void rotate(float degree);

    actor::ActorId shot();

    ~Cannon();
};

} // namespace game
} // namespace tung

#endif