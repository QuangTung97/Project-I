#ifndef LOGIC_STATE_START_STATE_HPP
#define LOGIC_STATE_START_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <memory>

namespace tung {
namespace state {

class StartState: GameState {
protected:

public:
    StartState(Manager& manager);

};

} // namespace state
} // namespace tung

#endif