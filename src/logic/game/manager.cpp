#include <logic/game/manager.hpp>
#include <logic/game/start_state.hpp>
#include <logic/game/playing_state.hpp>
#include <logic/game/end_state.hpp>
#include <graphics/gl/drawable.hpp>

namespace tung {
namespace state {

EventType<2322> STATE_MAKE_TRANSITION;

void Manager::init() {
    // Lắng nghe sự kiện chuyển đổi trạng thái  
    auto make_transition = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const MakeTransition&>(event_);
        make_transition_to(event.get_state());
    };
    transition_listener_ = make_transition;
    // Thêm nó vào event manager
    event_manager_.add_listener(STATE_MAKE_TRANSITION, transition_listener_);

    // Chia màn hình thành 3 nhóm 
    // Nhóm ở trong cùng, 
    // nhóm ở giữa và nhóm ngoài cùng 
    auto lower_group = std::make_shared<DrawableGroup>();
    auto middle_group = std::make_shared<DrawableGroup>();
    auto upper_group = std::make_shared<DrawableGroup>();
    root_drawable_->attach_drawable(lower_group);
    root_drawable_->attach_drawable(middle_group);
    root_drawable_->attach_drawable(upper_group);
    lower_group_ = lower_group;
    middle_group_ = middle_group;
    upper_group_ = upper_group;

    // Khởi tạo các trạng thái 
    start_ = std::make_unique<StartState>(*this);
    playing_ = std::make_unique<PlayingState>(*this);
    end_ = std::make_unique<EndState>(*this);

    // Gọi hàm entry của trạng thái đầu tiên 
    current_ = start_.get();
    current_->entry();
}

void Manager::make_transition_to(GameState& state) {
    // Gọi exit của trạng thái trước và entry của trạng thái sau 
    current_->exit();
    state.entry();
    current_ = &state;
}

bool Manager::on_mouse_event(MouseButton button,
        MouseEventType type, float x, float y) 
{
    return current_->on_mouse_event(button, type, x, y);       
}

bool Manager::on_key_event(const KeyEvent& event) {
    return current_->on_key_event(event);
}

Manager::~Manager() {
    // Gọi exit của trạng thái cuối cùng 
    current_->exit();
    // Xóa listener
    event_manager_.remove_listener(STATE_MAKE_TRANSITION, transition_listener_);
}

} // namespace state
} // namespace tung
