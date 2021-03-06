#ifndef GAME_LOGIC_STATE_MANAGER_HPP
#define GAME_LOGIC_STATE_MANAGER_HPP

#include "game_state.hpp"
#include <graphics/abstract/drawable.hpp>
#include <graphics/gl/image_drawable_factory.hpp>
#include <graphics/gl/sprite_factory.hpp>

#include <logic/abstract/event_manager.hpp>
#include <logic/basic/event.hpp>
#include <logic/basic/process_manager.hpp>
#include <sound/abstract/sound.hpp>
#include <asset_manager.hpp>
#include <view/abstract/view.hpp>

namespace tung {
namespace state {

extern EventType<2322> STATE_MAKE_TRANSITION;

// Sự kiện chuyển trạng thái của game 
class MakeTransition: public EventData {
private:
    GameState& state_;

public:
    // Constructor
    // @state: Trạng thái kế tiếp 
    MakeTransition(GameState& state)
    : EventData{TimePoint{}, STATE_MAKE_TRANSITION}, state_{state} {}

    IEventDataPtr clone() const override {
        return std::make_unique<MakeTransition>(state_);
    }

    // Return: Trạng thái kế tiếp 
    GameState& get_state() const {
        return state_;
    }
};

// Lớp quản lý các trạng thái của game 
class Manager {
private:
    friend class GameState;
    friend class StartState;
    friend class PlayingState;
    friend class EndState;

    GameState *current_;

    GameStatePtr start_;
    GameStatePtr playing_;
    GameStatePtr end_;

    EventListener transition_listener_;

private:
    IEventManager& event_manager_;
    ProcessManager& process_manager_;
    AssetManager& asset_manager_;
    ImageDrawableFactory& image_drawable_factory_;
    SpriteFactory& sprite_factory_;

    IDrawableManagerPtr root_drawable_;
    IDrawableManagerPtr lower_group_;
    IDrawableManagerPtr middle_group_;
    IDrawableManagerPtr upper_group_;

    IViewManagerPtr view_root_;

public:
    // Constructor
    // @manager: Tham chiếu đến bộ quản lý sự kiện 
    // @asset_manager: Tham chiếu đến bộ quản lý tài nguyên 
    // @image_drawable_factory: Tham chiếu đến factory sinh Image Drawable 
    // @sprite_factory: Tham chiếu đến factory sinh Sprite Drawable 
    // @root_drawable: Gốc của cây Drawable 
    // @view_root: Gốc của cây các phần tử UI 
    Manager(IEventManager& manager, 
        ProcessManager& process_manager,
        AssetManager& asset_manager,
        ImageDrawableFactory& image_drawable_factory,
        SpriteFactory& sprite_factory,
        IDrawableManagerPtr root_drawable,
        IViewManagerPtr view_root
    ): event_manager_{manager},
        process_manager_{process_manager},
        asset_manager_{asset_manager},
        image_drawable_factory_{image_drawable_factory},
        sprite_factory_{sprite_factory},
        root_drawable_{std::move(root_drawable)},
        view_root_{view_root}
    { init(); }

    // Khởi tạo 
    void init();

    // Chuyển trạng thái:
    // @state: Trạng thái tiếp theo 
    void make_transition_to(GameState& state);

    // Hàm sẽ được gọi khi một sự kiện chuột xảy ra 
    // @button: Nút đã bấm 
    // @type: Cách thức bấm 
    // @x, @y: Tọa độ của chuột 
    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y);

    // Hàm sẽ được gọi khi một sự kiện bàn phím xảy ra
    // @event: Sự kiện bàn phím đó 
    bool on_key_event(const KeyEvent& event);

    // Destructor
    ~Manager();

    //-------------------------------------------
    // Các hàm get tham chiếu đến các bộ quản lý 
    //-------------------------------------------
    IEventManager& get_event_manager() const {
        return event_manager_;
    }

    AssetManager& get_asset_manager() const {
        return asset_manager_;
    }

    IDrawableManager& root() const {
        return *middle_group_;
    }

    const IDrawableManagerPtr& get_root() const {
        return middle_group_;
    }

    const IViewManagerPtr& get_view_root() const {
        return view_root_;
    }

    IDrawableManagerPtr get_lower_group() const {
        return lower_group_;
    }

    IDrawableManagerPtr get_upper_group() const {
        return upper_group_;
    }

    ProcessManager& get_process_manager() const {
        return process_manager_;
    }

    ImageDrawableFactory& get_image_factory() const {
        return image_drawable_factory_;
    }

    SpriteFactory& get_sprite_factory() const {
        return sprite_factory_;
    }
};

}
} // namespace tung

#endif
