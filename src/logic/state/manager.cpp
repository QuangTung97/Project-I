#include <logic/state/manager.hpp>
#include <logic/state/start_state.hpp>

namespace tung {
namespace state {

void Manager::init() {
    start_ = std::make_unique<StartState>(*this);
    current_ = start_.get();
    current_->entry();
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