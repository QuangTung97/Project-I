#include <logic/game/end_state.hpp>
#include <logic/game/manager.hpp>

namespace tung {
namespace state {

EndState::EndState(Manager& manager)
: GameState(manager) 
{
    background_ = manager_.get_image_factory()
        .new_drawable("assets/end_background.png", 2);
}

void EndState::entry() {
    manager_.get_root()->attach_drawable(background_);
}

void EndState::exit() {
    manager_.get_root()->detach_drawable(background_);
}

bool EndState::on_mouse_event(MouseButton button,
    MouseEventType type, float x, float y) 
{
    return true;
}

} // namespace state
} // namespace tung