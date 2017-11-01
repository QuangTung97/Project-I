#include <logic/state/manager.hpp>

namespace tung {
namespace state {

Manager::Manager(IEventManager& manager, IDrawableManager& root_drawable)
: event_manager_{manager}, root_drawable_{root_drawable} {
}

void Manager::make_transition_to(GameState& state) {
    current_->exit();
    state.entry();
    current_ = &state;
}

bool Manager::on_mouse_event(MouseButton button,
        MouseEventType type, float x, float y) 
{
    return current_->on_mouse_event(button, type, x, y);       
}

} // namespace state
} // namespace tung