#include <root.hpp>
#include <graphics/image/png.hpp>
#include <graphics/gl/ui_shader_program.hpp>
#include <graphics/gl/simple_2d_shader.hpp>
#include <graphics/gl/texture.hpp>
#include <graphics/gl/vertex_object.hpp>
#include <graphics/gl/text_manager.hpp>
#include <view/image_view.hpp>
#include <view/text_view.hpp>
#include <view/abstract/keyboard.hpp>
#include <sound/sound.hpp>
#include <thread>
#include <unordered_map>

// Lớp dùng để khởi tạo toàn bộ chương trình 
namespace tung {

// Chuyển đổi kiểu giữa GLFW sang View 
const std::unordered_map<int, KeyButton> key_buttons = {
    {GLFW_KEY_ENTER, KeyButton::ENTER},
    {GLFW_KEY_SPACE, KeyButton::SPACE},
    {GLFW_KEY_LEFT, KeyButton::LEFT},
    {GLFW_KEY_RIGHT, KeyButton::RIGHT},
    {GLFW_KEY_UP, KeyButton::UP},
    {GLFW_KEY_DOWN, KeyButton::DOWN},
};

// Chuyển đổi kiểu giữa GLFW sang View 
const std::unordered_map<int, KeyType> key_types = {
    {GLFW_PRESS, KeyType::DOWN},
    {GLFW_RELEASE, KeyType::UP},
    {GLFW_REPEAT, KeyType::DOWN},
};

// @MouseButton button: có 4 loại: 
//      LEFT, MIDDLE, RIGHT, NONE ứng với chuột trái, chuột giữa, chuột phải 
//      và không có sự kiện ấn chuột 
// @MouseEventType type: có 3 loại: 
//      DOWN, UP và MOVE ứng với ấn nút, nhả nút chuột và rê chuột 
// Chuyển đổi từ  MouseButton, MouseEventType của GLFW 
// sang MouseEvent::Button, MouseEvent::Type của View 
// @x, y: tọa độ của chuột 
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

// Constructor 
Root::Root() {
    // Khoi tao man hinh, thu vien GLFW
    glfw_ = std::make_unique<GLFW>(640, 480, "Tung");

    // Thiet lap cac thuoc tinh cua OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Khoi tao factory cho viec load anh PNG
    image_loader_ = std::make_unique<PngImageLoader>();
    // Khoi tao factory to viec build texture
    texture_factory_ = std::make_unique<TextureFactory>();
    // Khoi tao bo quan ly am thanh
    sound_manager_ = std::make_unique<SoundManager>();

    // Khoi tao bo quan ly tai nguyen: 
    // Vi du: Anh, Texture va Am Thanh
    asset_manager_ = std::make_unique<AssetManager>(
        *image_loader_,
        *texture_factory_,
        *sound_manager_
    );

    // Thiet lap chuong trinh Shader cho OpenGL
    ui_program_ = std::make_unique<UIShaderProgram>("assets/ui.vs", "assets/ui.fs");
    _2d_program_ = std::make_unique<Simple2DShader>("assets/ui.vs", "assets/ui.fs");

    // Thiet lap builder cho cac Vertex Object cho cac chuong trinh Shader
    ui_object_builder_ = std::make_unique<VertexObjectBuilder>(*ui_program_);
    _2d_object_builder_ = std::make_unique<VertexObjectBuilder>(*_2d_program_);

    // Khoi tao bo quan ly hien thi text
    text_manager_ = std::make_unique<TextManager>(*texture_factory_, *_2d_object_builder_);

    // ImageView su dung asset manager va vertex object builder
    // Nen can truyen tham so
    ImageView::set_asset_manager(*asset_manager_);
    ImageView::set_vertex_object_builder(*ui_object_builder_);
    TextView::set_text_manager(*text_manager_);

    // Khoi tao factory tao hinh anh dong
    sprite_factory_ = std::make_unique<SpriteFactory>(
        *asset_manager_, *_2d_object_builder_);

    // Khoi tao factory tao hinh anh de ve len manh hinh (Vi du anh nen, anh may bay)
    image_drawable_factory_ = std::make_unique<ImageDrawableFactory>(
        *asset_manager_, *_2d_object_builder_);

    // Vong lap chinh cua game
    auto run_function = [this]() {
        // Dieu khien thoi gian
        // Buoc vong lap chi chay voi fps <= 60 (frame per second)
        if (prev_run_timestamp_ == steady_clock::time_point{}) {
            prev_run_timestamp_ = steady_clock::now();
        }
        else {
            auto dt = steady_clock::now() - prev_run_timestamp_;
            const nanoseconds frame_time{1'000'000'000 / fps_};
            std::this_thread::sleep_for(frame_time - dt);
            prev_run_timestamp_ = steady_clock::now();
        }

        // De am thanh co the duoc phat, can lien tuc update
        sound_manager_->update();

        // Quan ly va dap giua may bay và đạn 
        collision_system_->update();
        
        // Quản lý sự kiện của hệ thống
        event_manager_->update();

        // Tính toán khoảng thời gian giữa vòng lặp trước và vòng lặp hiện tại 
        if (prev_timestamp_ == TimePoint{}) {
            prev_timestamp_ = timer_->current_time();
        }
        milliseconds dt = duration_cast<milliseconds>(
            timer_->current_time() - prev_timestamp_);
        prev_timestamp_ += dt;
        // Update các tiến trình con theo độ lệch thời gian đó 
        // Các tiến trình con có thể bao gồm:
        // + Tiến trình cho máy bay chuyển động 
        // + Tiến trình cho đạn bay 
        // + Tiến trình sinh máy bay ngẫu nhiên 
        process_manager_->update_processes(dt);

        // Xóa toàn bộ màn hình
		glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

        // Vẽ các thành phần ứng với từng loại shader 

        // Shader dành cho hiện thị những object trong game. 
        // Ví dụ: súng, đạn, máy bay. 
        _2d_program_->predraw(640, 480);
        _2d_program_->draw();
        _2d_program_->postdraw();

        // Shader dành cho Hiện thị UI 
        ui_program_->predraw(640, 480);
        ui_program_->draw();
        ui_program_->postdraw();
    };

    // Set callback để hàm run có thể được gọi liên tục 
    glfw_->set_run_callback(run_function);

    // Thiết lập gốc của cây chứa các object trong game
    auto root = std::make_shared<DrawableGroup>();
    _2d_program_->set_drawable(root);

    // Thiết lập gốc của UI trong game
    view_root_ = std::make_shared<ViewGroup>(
        0, 0,
        GLFW::get_screen_width(),
        GLFW::get_screen_height()
    );
    ui_program_->set_drawable(view_root_->get_drawable());

    // Khởi tạo các manager thiết yếu cho game
    // Event manager: Quản lý sự kiện của game. 
    event_manager_ = std::make_unique<EventManager>();

    // Process Manager: Quản lý các tiến trình con trong game. 
    process_manager_ = std::make_unique<ProcessManager>();

    // Timer: Quản lý thời gian của game. 
    timer_ = std::make_unique<Timer>(*event_manager_);

    // Game Logic: Quản lý các actor trong game. 
    // Actor bao gồm tất cả các object. 
    // Ví dụ như máy bay, đạn, bệ súng, súng đều là các Actor. 
    // Và đều có một ActorId duy nhất với chúng. 
    game_logic_ = std::make_unique<GameLogic>(*event_manager_);

    // Khởi tạo bộ quản lý âm thanh của game. 
    sound_system_ = std::make_unique<system::Sound>(*event_manager_);

    // Khởi tạo bộ điều khiển va đập
    collision_system_ = std::make_unique<system::Collision>(*event_manager_, *timer_);

    // Khởi tạo bộ điều khiển hình ảnh động 
    sprite_system_ = std::make_unique<system::Sprite>(*event_manager_);

    // Khởi tạo bộ quản lý đồ họa 
    // (Đồ họa ở đây chỉ bao gồm những hình ảnh 2D)
    graphics_system_ = std::make_unique<system::Graphics>(*event_manager_);

    // Quản lý trạng thái của game
    // Mỗi một trạng thái ứng với một màn hình 
    // Trong game hiện tại chỉ có 2 trạng thái. 
    // + Trạng thái bắt đầu (start_state)
    // + Trạng thái chơi (playing_state)
    state_manager_ = std::make_unique<state::Manager>(
        *event_manager_,
        *process_manager_,
        *asset_manager_,
        *image_drawable_factory_,
        *sprite_factory_,
        root,
        view_root_
    );

    // Thiết lập callback xử lý sự kiện chuột 
    MouseEventListener mouse_listener = 
    [this](MouseButton button, 
        MouseEventType type, float x, float y) {
        MouseEvent view_event = get_view_mouse_event(button, type, x, y);
        view_root_->on_mouse_event(view_event);
        state_manager_->on_mouse_event(button, type, x, y);
    };
    glfw_->set_mouse_listener(mouse_listener);

    // Thiết lập callback xử lý sự kiện bàn phím 
    KeyEventListener key_listener = 
    [this](int key, int scancode, int action, int mods) {
        // Kiểm tra xem nút đó có nằm trong tập được chấp nhận không 
        auto button_it = key_buttons.find(key);
        if (button_it == key_buttons.end())
            return;
        KeyButton button = button_it->second;
        
        // Kiểm tra xem type của nút đó có nằm trong tập được chấp nhận không 
        auto type_it = key_types.find(action);
        if (type_it == key_types.end())
            return;
        KeyType type = type_it->second;
        
        // Thiết lập các giá trị của các nút Modifier 
        KeyModifier modifiers;
        modifiers[static_cast<size_t>(KeyMod::SHIFT)] = mods & GLFW_MOD_SHIFT;
        modifiers[static_cast<size_t>(KeyMod::CONTROL)] = mods & GLFW_MOD_CONTROL;
        modifiers[static_cast<size_t>(KeyMod::ALT)] = mods & GLFW_MOD_ALT;
        modifiers[static_cast<size_t>(KeyMod::SUPER)] = mods & GLFW_MOD_SUPER;

        // Tạo một KeyEvent 
        const KeyEvent event{button, type, modifiers};
        // Gửi nó cho các view 
        view_root_->on_key_event(event);
        // Gửi nó cho các trạng thái trong game
        state_manager_->on_key_event(event);
    };
    glfw_->set_key_callback(key_listener);

    view_root_->focus(true);
}

// Chạy vòng lặp 
void Root::run() {
    glfw_->run();
}

// Destructor 
Root::~Root() {
    // Hủy tất cả các tiến trình con đang chạy 
    process_manager_->abort_all_processes();
    // Update lại event manager để tránh các sự kiện còn xót lại trong hàng đợi 
    event_manager_->update();
}

} // namespace tung

// Hàm main, 
int main() {
    tung::Root root;
    root.run();
    return 0;
}
