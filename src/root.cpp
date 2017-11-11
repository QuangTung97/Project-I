#include <root.hpp>
#include <graphics/image/png.hpp>
#include <graphics/gl/ui_shader_program.hpp>
#include <graphics/gl/simple_2d_shader.hpp>
#include <graphics/gl/texture.hpp>
#include <graphics/gl/vertex_object.hpp>
#include <graphics/gl/text_manager.hpp>
#include <view/image_view.hpp>
#include <view/text_view.hpp>
#include <sound/sound.hpp>
#include <thread>

namespace tung {

MouseEvent get_view_mouse_event(
    MouseButton button, MouseEventType type, 
    float x, float y) 
{
    MouseEvent::Button view_button;
    MouseEvent::Type view_type;

    switch (button) {
    case MouseButton::LEFT:
        view_button = MouseEvent::Button::LEFT;
        break;

    case MouseButton::RIGHT:
        view_button = MouseEvent::Button::RIGHT;
        break;

    case MouseButton::MIDDLE:
        view_button = MouseEvent::Button::MIDDE;
        break;
    
    case MouseButton::NONE:
        view_button = MouseEvent::Button::NONE;
        break;

    default:
        break;
    }

    switch (type) {
    case MouseEventType::DOWN:
        view_type = MouseEvent::Type::MOUSE_DOWN;
        break;

    case MouseEventType::UP:
        view_type = MouseEvent::Type::MOUSE_UP;
        break;
        
    case MouseEventType::MOVE:
        view_type = MouseEvent::Type::MOUSE_MOVE;
        break;

    default:
        break;
    }

    return MouseEvent{view_button, view_type, x, y};
}

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

    text_manager_ = std::make_unique<TextManager>(*texture_factory_, *_2d_object_builder_);

    ImageView::set_asset_manager(*asset_manager_);
    ImageView::set_vertex_object_builder(*ui_object_builder_);
    TextView::set_text_manager(*text_manager_);

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

    auto background = std::make_shared<ImageView>(0, 0, 
        640, 480, "assets/llvm.png");

    auto root = std::make_shared<DrawableGroup>();
    _2d_program_->set_drawable(root);

    view_root_ = std::make_shared<ViewGroup>(
        0, 0,
        GLFW::get_screen_width(),
        GLFW::get_screen_height()
    );
    ui_program_->set_drawable(view_root_->get_drawable());

    // Game Logic
    event_manager_ = std::make_unique<EventManager>();
    process_manager_ = std::make_unique<ProcessManager>();
    timer_ = std::make_unique<Timer>(*event_manager_);
    game_logic_ = std::make_unique<GameLogic>(*event_manager_);

    // Game Logic - Systems
    sound_system_ = std::make_unique<system::Sound>(*event_manager_);
    collision_system_ = std::make_unique<system::Collision>(*event_manager_, *timer_);
    sprite_system_ = std::make_unique<system::Sprite>(*event_manager_);
    graphics_system_ = std::make_unique<system::Graphics>(*event_manager_);

    state_manager_ = std::make_unique<state::Manager>(
        *event_manager_,
        *process_manager_,
        *asset_manager_,
        *image_drawable_factory_,
        *sprite_factory_,
        *sound_manager_,
        root,
        view_root_
    );

    // Mouse Event
    MouseEventListener mouse_listener = 
    [this](MouseButton button, 
        MouseEventType type, float x, float y) {
        MouseEvent view_event = get_view_mouse_event(button, type, x, y);
        view_root_->on_mouse_event(view_event);
        state_manager_->on_mouse_event(button, type, x, y);
    };
    glfw_->set_mouse_listener(mouse_listener);
}

void Root::run() {
    glfw_->run();
}

Root::~Root() {
    process_manager_->abort_all_processes();
    event_manager_->update();
}

} // namespace tung

int main() {
    tung::Root root;
    root.run();
    return 0;
}