#include <logic/game/manager.hpp>
#include <logic/game/start_state.hpp>
#include <logic/game/playing_state.hpp>
#include <logic/game/end_state.hpp>
#include <graphics/gl/drawable.hpp>

namespace tung {
namespace state {

void Manager::init() {
    auto lower_group = std::make_shared<DrawableGroup>();
    auto middle_group = std::make_shared<DrawableGroup>();
    auto upper_group = std::make_shared<DrawableGroup>();
    root_drawable_->attach_drawable(lower_group);
    root_drawable_->attach_drawable(middle_group);
    root_drawable_->attach_drawable(upper_group);
    lower_group_ = lower_group;
    middle_group_ = middle_group;
    upper_group_ = upper_group;

    start_ = std::make_unique<StartState>(*this);
    playing_ = std::make_unique<PlayingState>(*this);
    end_ = std::make_unique<EndState>(*this);

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