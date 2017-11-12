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

namespace tung {
namespace state {

class PlayingState: public GameState {
private:
    friend class PlaneGenerator;

    IDrawablePtr background_;
    std::shared_ptr<game::Cannon> cannon_;
    StrongProcessPtr plane_generator_;
    std::unordered_set<actor::ActorId> planes_;
    std::unordered_set<actor::ActorId> bullets_;

    EventListener plane_destroy_listener_;
    EventListener collide_listener_;

    int score_ = 0;
    int high_score_;

    int heart_count_ = 4;

    std::shared_ptr<TextView> show_score_;
    std::shared_ptr<TextView> show_high_score_;

    std::vector<std::shared_ptr<ImageView>> heart_views;

    void increase_score(int value);

    void load_high_score();

    void store_high_score();

public:
    PlayingState(Manager& manager);

    void entry() override;

    void exit() override;

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y) override;
};

} // namespace state
} // namespace tung

#endif