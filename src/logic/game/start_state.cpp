#include <logic/game/manager.hpp>
#include <logic/game/start_state.hpp>
#include <iostream>

namespace tung {
namespace state {

StartState::StartState(Manager& manager)
: GameState(manager) {
    background_ = manager.get_image_factory().
        new_drawable("assets/start_background.png", 2.0);
}

void StartState::entry() {
    manager_.root().attach_drawable(background_);
}

void StartState::exit() {
    manager_.root().detach_drawable(background_);
}

bool StartState::on_mouse_event(MouseButton button,
    MouseEventType type, float x, float y) 
{
    if (button == MouseButton::LEFT && type == MouseEventType::DOWN)
        manager_.make_transition_to(*manager_.playing_);
    return true;
}

} // namespace state
} // namespace tung