#ifndef LOGIC_STATE_PLAYING_STATE_HPP
#define LOGIC_STATE_PLAYING_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <memory>

namespace tung {
namespace state {

class PlayingState: GameState {
protected:

public:
    PlayingState(Manager& manager);

};

} // namespace state
} // namespace tung

#endif