#ifndef LOGIC_STATE_PLAYING_STATE_HPP
#define LOGIC_STATE_PLAYING_STATE_HPP

#include "game_state.hpp"
#include <graphics/gl/drawable.hpp>
#include <logic/game/cannon.hpp>
#include <logic/abstract/process.hpp>
#include <memory>
#include <vector>
#include <unordered_set>
#include <view/text_view.hpp>
#include <view/image_view.hpp>

#include "level_manager.hpp"

namespace tung {

namespace actor {
class CollideEvent;
};

namespace game {
class FlyProcess;
}

namespace state {

class LevelManager;

// Lớp thể hiện trạng thái đang chơi
// Chỉ có duy nhất một object của class này trong game 
class PlayingState: public GameState {
private:
    friend class PlaneGenerator;
    friend class PlaneGeneratorV2;
    friend class game::FlyProcess;

    std::unique_ptr<LevelManager> level_manager_;

    IDrawablePtr background_;
    std::shared_ptr<game::Cannon> cannon_;
    std::unordered_set<actor::ActorId> planes_;
    std::unordered_set<actor::ActorId> bullets_;
    std::unordered_set<actor::ActorId> bombs_;

    EventListener plane_destroy_listener_;
    EventListener collide_listener_;

    int score_ = 0;
    int high_score_;

    const int max_heart_count_ = 4;
    int heart_count_ = max_heart_count_;

    std::shared_ptr<TextView> show_score_;
    std::shared_ptr<TextView> show_high_score_;

    std::vector<std::shared_ptr<ImageView>> heart_views;
    std::shared_ptr<ViewGroup> heart_view_group_;

    // Khởi tạo các view hiển thị mạng 
    void init_heart_views();

    // Thiết lập lại giá trị mạng đang có 
    void reset_heart_count();

    // Giảm mạng 
    void reduce_heart_count(int value);

    // Thiết lập lại điểm số 
    void reset_score(); 

    // Tăng điểm 
    void increase_score(int value);

    // Load điểm cao từ file lên 
    void load_high_score();

    // Lưu trữ điểm cao xuống file 
    void store_high_score();

    // Xử lý sự kiện va chạm 
    // @event: Sự kiện va chạm 
    void handle_collide_event(const actor::CollideEvent& event);

public:
    // Constructor
    // @manager: Tham chiếu đến bộ quản lý trạng thái 
    PlayingState(Manager& manager);

    void entry() override;

    void exit() override;

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y) override;

    bool on_key_event(const KeyEvent& event) override;
};

} // namespace state
} // namespace tung

#endif
