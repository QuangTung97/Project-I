#include <logic/game/manager.hpp>
#include <logic/game/start_state.hpp>
#include <view/text_view.hpp>

namespace tung {
namespace state {

StartState::StartState(Manager& manager)
: GameState(manager) {
    background_ = manager.get_image_factory().
        new_drawable("assets/start_background.png", 2.0);

    /*
    auto text = std::make_shared<TextView>(
        100, 100, 48, Color::RED, "Score: 100"
    );
    manager_.get_view_root()->add_view(text);
    */
    
    manager_.get_asset_manager().get_image("assets/playing_background.png");
    manager_.get_asset_manager().get_image("assets/start_background.png");
    manager_.get_asset_manager().get_image("assets/bullet.png");
    manager_.get_asset_manager().get_image("assets/cannon_base.png");
    manager_.get_asset_manager().get_image("assets/cannon_head.png");
    manager_.get_asset_manager().get_image("assets/end_background.png");
    manager_.get_asset_manager().get_image("assets/explosion1.png");
    manager_.get_asset_manager().get_sound("assets/plane_explode.mp3");
    manager_.get_asset_manager().get_image("assets/fighter1.png");
    manager_.get_asset_manager().get_image("assets/fighter2.png");
    manager_.get_asset_manager().get_image("assets/fighter3.png");
        
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