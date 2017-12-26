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

    void init_heart_views();

    void reset_heart_count();

    void reduce_heart_count(int value);

    void reset_score(); 

    void increase_score(int value);

    void load_high_score();

    void store_high_score();

    void handle_collide_event(const actor::CollideEvent& event);

public:
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