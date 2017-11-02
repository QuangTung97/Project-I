#include <root.hpp>
#include <graphics/image/png.hpp>
#include <graphics/gl/ui_shader_program.hpp>
#include <graphics/gl/simple_2d_shader.hpp>
#include <graphics/gl/texture.hpp>
#include <graphics/gl/vertex_object.hpp>
#include <view/image_view.hpp>
#include <sound/sound.hpp>
#include <thread>

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

    ImageView::set_asset_manager(*asset_manager_);
    ImageView::set_vertex_object_builder(*ui_object_builder_);

    sprite_factory_ = std::make_unique<SpriteFactory>(
        *asset_manager_, *_2d_object_builder_);

    image_drawable_factory_ = std::make_unique<ImageDrawableFactory>(
        *asset_manager_, *_2d_object_builder_);

    auto run_function = [this]() {
        // Control Time
        if (prev_run_timestamp_ == steady_clock::time_point{}) {
            prev_run_timestamp_ = steady_clock::now();
        }
        else {
            auto dt = steady_clock::now() - prev_run_timestamp_;
            const nanoseconds frame_time{1'000'000'000 / fps_};
            std::this_thread::sleep_for(frame_time - dt);
            prev_run_timestamp_ = steady_clock::now();
        }

        sound_manager_->update();
        collision_system_->update();
        event_manager_->update();

        if (prev_timestamp_ == TimePoint{}) {
            prev_timestamp_ = timer_->current_time();
        }
        milliseconds dt = duration_cast<milliseconds>(
            timer_->current_time() - prev_timestamp_);
        prev_timestamp_ += dt;
        process_manager_->update_processes(dt);

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

    auto background = std::make_shared<ImageView>(0, 0, 
        640, 480, "assets/llvm.png");

    // ui_program_->set_drawable(background->get_drawable());

    auto root = std::make_shared<DrawableGroup>();
    auto sprite = sprite_factory_->new_sprite(
        "assets/explosion1.png", 6, 8, 0.4);
    sprite->use_sprite(8);
    sprite->translate({0.5, 0, 0});

    root->attach_drawable(sprite);
    _2d_program_->set_drawable(root);

    // Game Logic
    event_manager_ = std::make_unique<EventManager>();
    process_manager_ = std::make_unique<ProcessManager>();
    timer_ = std::make_unique<Timer>(*event_manager_);
    game_logic_ = std::make_unique<GameLogic>(*event_manager_);

    // Game Logic - Systems
    sound_system_ = std::make_unique<system::Sound>(*event_manager_);
    collision_system_ = std::make_unique<system::Collision>(*event_manager_, *timer_);
    sprite_system_ = std::make_unique<system::Sprite>(*event_manager_);

    sprite_component_ = std::make_unique<actor::Sprite>(
        root, *sprite_factory_, *process_manager_);

    sprite_component_->add_sprite(0, "assets/explosion1.png", 6, 8, 0.6);
    sprite_component_->start(0);
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