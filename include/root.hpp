#ifndef GAME_ROOT_HPP
#define GAME_ROOT_HPP

#include <memory>
#include <graphics/gl/glfw.hpp>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/abstract/image.hpp>
#include <graphics/abstract/texture.hpp>
#include <graphics/abstract/text_factory.hpp>

#include <sound/abstract/sound.hpp>
#include <asset_manager.hpp>

#include <view/view.hpp>

#include <logic/basic/event_manager.hpp>
#include <logic/basic/process_manager.hpp>
#include <logic/basic/timer.hpp>
#include <logic/game_logic.hpp>

#include <logic/system/sound.hpp>
#include <logic/system/collision.hpp>
#include <logic/system/sprite.hpp>
#include <logic/system/graphics.hpp>

#include <graphics/gl/sprite_factory.hpp>
#include <graphics/gl/image_drawable_factory.hpp>

#include <logic/actor/sprite.hpp>
#include <logic/game/manager.hpp>

namespace tung {

class Root {
private:
    std::unique_ptr<GLFW> glfw_;
    
    std::unique_ptr<IImageLoader> image_loader_;
    std::unique_ptr<ITextureFactory> texture_factory_;
    std::unique_ptr<ISoundManager> sound_manager_;
    std::unique_ptr<AssetManager> asset_manager_;

    std::unique_ptr<IShaderProgram> ui_program_;
    std::unique_ptr<IShaderProgram> _2d_program_;

    std::unique_ptr<IVertexObjectBuilder> ui_object_builder_;
    std::unique_ptr<IVertexObjectBuilder> _2d_object_builder_;

    std::unique_ptr<ITextFactory> text_factory_;

    std::unique_ptr<SpriteFactory> sprite_factory_;
    std::unique_ptr<ImageDrawableFactory> image_drawable_factory_;

    // Game Logic
    std::unique_ptr<EventManager> event_manager_;
    std::unique_ptr<ProcessManager> process_manager_;
    TimePoint prev_timestamp_; // Use for Process Manager
    std::unique_ptr<Timer> timer_;
    std::unique_ptr<GameLogic> game_logic_;

    // Game Logic - Systems
    std::unique_ptr<system::Sound> sound_system_;
    std::unique_ptr<system::Collision> collision_system_;
    std::unique_ptr<system::Sprite> sprite_system_;
    std::unique_ptr<system::Graphics> graphics_system_;

    // Control Time
    steady_clock::time_point prev_run_timestamp_;
    const long fps_ = 60;

    std::unique_ptr<state::Manager> state_manager_;
    std::shared_ptr<ViewGroup> view_root_;

public:
    Root();

    void run();

    ~Root();
};

} // namespace tung

#endif