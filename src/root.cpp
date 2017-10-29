#include <root.hpp>
#include <graphics/image/png.hpp>
#include <graphics/gl/ui_shader_program.hpp>
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

    program_ = std::make_unique<UIShaderProgram>("asset/ui.vs", "asset/ui.fs");

    object_builder_ = std::make_unique<VertexObjectBuilder>(*program_);

    ImageView::set_texture_factory(*texture_factory_);
    ImageView::set_vertex_object_builder(*object_builder_);

    sound_manager_ = std::make_unique<SoundManager>();

    auto run_function = [this]() {
		glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

        program_->predraw(640, 480);
        program_->draw();
        program_->postdraw();

        collision_system_->update();
        event_manager_->update();
    };

    glfw_->set_run_callback(run_function);
    // TODO
    // set_char_callback
    // set_mouse_listener

    auto image = image_loader_->load("asset/cute.png");
    auto image_view = std::make_shared<tung::ImageView>(
            50, 50, 100, 100, image);
    program_->set_drawable(image_view->get_drawable());

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