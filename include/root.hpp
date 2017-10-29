#ifndef GAME_ROOT_HPP
#define GAME_ROOT_HPP

#include <memory>
#include <graphics/gl/glfw.hpp>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/abstract/image.hpp>
#include <graphics/abstract/texture.hpp>
#include <sound/abstract/sound.hpp>
#include <logic/basic/event_manager.hpp>
#include <logic/basic/process_manager.hpp>
#include <logic/basic/timer.hpp>
#include <logic/system/sound.hpp>
#include <logic/system/collision.hpp>
#include <logic/game_logic.hpp>

#include <graphics/gl/sprite_factory.hpp>
#include <graphics/gl/image_drawable_factory.hpp>

namespace tung {

class Root {
private:
    std::unique_ptr<GLFW> glfw_;
    std::unique_ptr<IShaderProgram> ui_program_;
    std::unique_ptr<IShaderProgram> _2d_program_;
    std::unique_ptr<IImageLoader> image_loader_;
    std::unique_ptr<ITextureFactory> texture_factory_;
    std::unique_ptr<IVertexObjectBuilder> ui_object_builder_;
    std::unique_ptr<IVertexObjectBuilder> _2d_object_builder_;

    std::unique_ptr<SpriteFactory> sprite_factory_;
    std::unique_ptr<ImageDrawableFactory> image_drawable_factory_;

    // Sound
    std::unique_ptr<ISoundManager> sound_manager_;

    // Logic
    std::unique_ptr<EventManager> event_manager_;
    std::unique_ptr<ProcessManager> process_manager_;
    std::unique_ptr<Timer> timer_;
    std::unique_ptr<system::Sound> sound_system_;
    std::unique_ptr<system::Collision> collision_system_;
    std::unique_ptr<GameLogic> game_logic_;

public:
    Root();

    void run();

    ~Root();
};

} // namespace tung

#endif