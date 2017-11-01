#include <root.hpp>
#include <graphics/image/png.hpp>
#include <graphics/gl/ui_shader_program.hpp>
#include <graphics/gl/simple_2d_shader.hpp>
#include <graphics/gl/texture.hpp>
#include <graphics/gl/vertex_object.hpp>
#include <view/image_view.hpp>
#include <sound/sound.hpp>

namespace tung {

Root::Root() {
    glfw_ = std::make_unique<GLFW>(640, 480, "Tung");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    image_loader_ = std::make_unique<PngImageLoader>();
    texture_factory_ = std::make_unique<TextureFactory>();
    sound_manager_ = std::make_unique<SoundManager>();

    asset_manager_ = std::make_unique<AssetManager>(
        *image_loader_,
        *texture_factory_,
        *sound_manager_
    );

    ui_program_ = std::make_unique<UIShaderProgram>("assets/ui.vs", "assets/ui.fs");
    _2d_program_ = std::make_unique<Simple2DShader>("assets/ui.vs", "assets/ui.fs");

    ui_object_builder_ = std::make_unique<VertexObjectBuilder>(*ui_program_);
    _2d_object_builder_ = std::make_unique<VertexObjectBuilder>(*_2d_program_);

    ImageView::set_texture_factory(*texture_factory_);
    ImageView::set_vertex_object_builder(*ui_object_builder_);

    sprite_factory_ = std::make_unique<SpriteFactory>(
        *asset_manager_, *_2d_object_builder_);

    image_drawable_factory_ = std::make_unique<ImageDrawableFactory>(
        *asset_manager_, *_2d_object_builder_);

    auto run_function = [this]() {
        sound_manager_->update();
        collision_system_->update();
        event_manager_->update();

		glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

        _2d_program_->predraw(640, 480);
        _2d_program_->draw();
        _2d_program_->postdraw();

        ui_program_->predraw(640, 480);
        ui_program_->draw();
        ui_program_->postdraw();
    };

    glfw_->set_run_callback(run_function);
    // TODO
    // set_char_callback
    // set_mouse_listener

    auto sprite = sprite_factory_->new_sprite(
        "assets/explosion1.png", 6, 8, 0.4);
    sprite->use_sprite(8);
    sprite->translate({0.5, 0, 0});
    _2d_program_->set_drawable(sprite);

    // Game Logic
    event_manager_ = std::make_unique<EventManager>();
    process_manager_ = std::make_unique<ProcessManager>();
    timer_ = std::make_unique<Timer>(*event_manager_);
    sound_system_ = std::make_unique<system::Sound>(*event_manager_);
    collision_system_ = std::make_unique<system::Collision>(*event_manager_, *timer_);
    game_logic_ = std::make_unique<GameLogic>(*event_manager_);
}

void Root::run() {
    glfw_->run();
}

Root::~Root() {
}

} // namespace tung

int main() {
    tung::Root root;
    root.run();
    return 0;
}