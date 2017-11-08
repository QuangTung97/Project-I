#ifndef GAME_LOGIC_STATE_MANAGER_HPP
#define GAME_LOGIC_STATE_MANAGER_HPP

#include "game_state.hpp"
#include <graphics/abstract/drawable.hpp>
#include <graphics/gl/image_drawable_factory.hpp>
#include <logic/abstract/event_manager.hpp>
#include <logic/basic/process_manager.hpp>

namespace tung {
namespace state {

class Manager {
private:
    friend class GameState;
    GameState *current_;

    GameStatePtr start_;
    GameStatePtr playing_;
    GameStatePtr end_;

private:
    IEventManager& event_manager_;
    ProcessManager& process_manager_;
    ImageDrawableFactory& image_drawable_factory_;
    IDrawableManagerPtr root_drawable_;

public:
    Manager(IEventManager& manager, 
        ProcessManager& process_manager,
        ImageDrawableFactory& image_drawable_factory,
        IDrawableManagerPtr root_drawable
    ): event_manager_{manager},
        process_manager_{process_manager},
        image_drawable_factory_{image_drawable_factory},
        root_drawable_{std::move(root_drawable)}
    { init(); }

    void init();

    void make_transition_to(GameState& state);

    bool on_mouse_event(MouseButton button, 
        MouseEventType type, float x, float y);

    IEventManager& get_event_manager() const {
        return event_manager_;
    }

    IDrawableManager& root() const {
        return *root_drawable_;
    }

    ProcessManager& get_process_manager() const {
        return process_manager_;
    }

    ImageDrawableFactory& get_image_factory() const {
        return image_drawable_factory_;
    }
};

}
} // namespace tung

#endif