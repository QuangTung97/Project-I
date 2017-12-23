#ifndef LOGIC_GAME_LEVEL_MANAGER_HPP
#define LOGIC_GAME_LEVEL_MANAGER_HPP

#include "playing_state.hpp"
#include <view/text_view.hpp>
#include <logic/abstract/process.hpp>
#include <logic/basic/process_manager.hpp>
#include <view/abstract/view.hpp>

namespace tung {
namespace state {

class PlayingState;

class LevelManager {
private:
    PlayingState& playing_state_;
    ProcessManager& process_manager_;
    int level_ = 0;
    std::shared_ptr<TextView> text_level_;
    std::shared_ptr<TextView> text_new_level_;
    StrongProcessPtr plane_generator_;
    IViewManager& root_;

    void show_new_level();

public:
    LevelManager(
            PlayingState& playing_state,
            ProcessManager& process_manager,
            IViewManager& root
    ) 
    : playing_state_{playing_state},
        process_manager_{process_manager},
        root_{root}
        {}

    void init();

    void next_level();

    int level() const { return level_; }

    void entry();

    void exit();

    ~LevelManager() {}
};

} // namespace state
} // namespace tung

#endif 