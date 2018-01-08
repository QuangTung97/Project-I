#include <graphics/gl/glfw.hpp>
#include <exception>

namespace tung {

glfw_exception::glfw_exception(std::string error)
    : what_{std::move(error)} {}

const char *glfw_exception::what() const noexcept {
    // Trả về con trỏ đến xâu what
    return what_.c_str();
}

GLFW *GLFW::this_ = nullptr;

GLFW::GLFW(int width, int height, 
        const std::string& name, bool resizable) {
    // Lưu trữ kích thước màn hình 
    screen_width_ = width;
    screen_height_ = height;
    // Gán địa chỉ cho con trỏ global trỏ tới Object GLFW 
    this_ = this;
    // Khởi tạo 
    if (!::glfwInit()) {
        // Nếu khởi tạo không thành công 
        // Throw 1 ngoại lệ 
        this_ = nullptr;
        throw glfw_exception("Can't init");
    }

    // Nếu không thể thay đổi kích thước 
    if (!resizable) 
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Tạo cửa sổ
    window_ = ::glfwCreateWindow(width, height, 
            name.c_str(), nullptr, NULL);

    // Nếu cửa sổ không được tạo ra 
    if (!window_) {
        // Kết thúc glfw 
        ::glfwTerminate();
        this_ = nullptr;
        // Throw một ngoại lệ
        throw glfw_exception("Can't create window");
    }

    // Thiết lập cửa sổ hiện tại 
	::glfwMakeContextCurrent(window_);

    // Thiết lập các hàm callback ứng với từng sự kiện
    // Đóng cửa sổ 
    // Thay đổi kích thước cửa sổ 
    // Ấn phím 
    // Ấn kí tự 
    // Ấn chuột 
    // chuột thay đổi vị trí 
    ::glfwSetWindowCloseCallback(window_, 
            static_window_close_callback);
    ::glfwSetWindowSizeCallback(window_,
            static_window_size_callback);
    ::glfwSetKeyCallback(window_, static_key_callback);
    ::glfwSetCharCallback(window_, static_char_callback);
    ::glfwSetMouseButtonCallback(window_, static_mouse_callback);
    ::glfwSetCursorPosCallback(window_, static_mouse_pos_callback);

    // Kích hoạt các chức năng thử nghiệm 
	::glewExperimental = GL_TRUE;
    // Khởi tạo glew 
	::glewInit();
}

void GLFW::set_run_callback(std::function<void()> func) {
    // Gán giá trị run callback 
    run_callback_ = std::move(func);
}

void GLFW::set_window_size_callback(
        std::function<void(int, int)> func) {
    // Gán giá trị window size callback 
    window_size_callback_ = std::move(func);
}

void GLFW::set_key_callback(
        std::function<void(int, int, int, int)> func) {
    // Gán giá trị key callback 
    key_callback_ = std::move(func);
}

void GLFW::set_char_callback(
        std::function<void(unsigned int)> func) {
    // Gán giá trị char callback 
    char_callback_ = std::move(func);
}

void GLFW::set_mouse_listener(MouseEventListener listener) {
    // Gán giá trị mouse callback 
    mouse_listener_ = listener;
}

void GLFW::run() {
    // Kích hoạt vsync
    glfwSwapInterval(1);
    // Trong khi cửa sổ chưa đóng 
    while (!::glfwWindowShouldClose(window_)) {
        // Chạy hàm run callback 
        if (run_callback_)
            run_callback_();
        // Lấy sự kiện 
        ::glfwPollEvents();
        // Swap buffer
        ::glfwSwapBuffers(window_);
    }
}

GLFWwindow *GLFW::window() const noexcept {
    return window_;
}

GLFW::~GLFW() {
    // Xóa cửa sổ 
    ::glfwDestroyWindow(window_);
    window_ = nullptr;
    // Kết thúc GLFW
    ::glfwTerminate();
    this_ = nullptr;
}

void GLFW::window_close_callback() {
}

void GLFW::window_size_callback(int width, int height) {
    // Nếu có window size callback 
    if (window_size_callback_)
        window_size_callback_(width, height);
}

void GLFW::key_callback(int key, int scancode, 
        int action, int mods) {
    // Nếu có key callback 
    if (key_callback_)
        key_callback_(key, scancode, action, mods);
}

void GLFW::char_callback(unsigned int code) {
    // Nếu có char callback 
    if (char_callback_)
        char_callback_(code);
}

void GLFW::mouse_pos_callback(double xpos, double ypos) {
    // Lưu tữ tọa độ của chuột 
    x_ = xpos;
    y_ = ypos;

    // Nếu mouse call không tồn tại thì trả về 
    if (mouse_listener_ == nullptr)
        return;

    MouseEventType event_type = MouseEventType::MOVE;
    MouseButton event_button = MouseButton::NONE;

    // Tạo một event chuột di chuyển 
    // Và gửi đến mouse callback 
    mouse_listener_(event_button, event_type, x_, y_);

    // Nếu trong lúc đó mà chuột trái được ấn 
    if (left_pressed_) {
        event_button = MouseButton::LEFT;   
        // Tạo một event chuột trái được kéo thả 
        // Và gửi đến mouse callback 
        mouse_listener_(event_button, event_type, x_, y_);
    }
    
    // Tương tự với chuột phải 
    if (right_pressed_) {
        event_button = MouseButton::RIGHT;
        mouse_listener_(event_button, event_type, x_, y_);
    }

    // Tương tự với chuột trái 
    if (middle_pressed_) {
        event_button = MouseButton::MIDDLE;
        mouse_listener_(event_button, event_type, x_, y_);
    }
}

void GLFW::mouse_callback(int button, int action, int) {
    // Nếu không có mouse callback thì trả về 
    if (mouse_listener_ == nullptr)
        return;

    // Dự vào giá trị button, action
    // để thay đổi các biến boolean tương ứng 
    MouseButton event_button;
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        event_button = MouseButton::LEFT;
        if (action == GLFW_PRESS)
            left_pressed_ = true;
        else
            left_pressed_ = false;
        break;

    case GLFW_MOUSE_BUTTON_RIGHT:
        event_button = MouseButton::RIGHT;
        if (action == GLFW_PRESS)
            right_pressed_ = true;
        else
            right_pressed_ = false;
        break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
        event_button = MouseButton::MIDDLE;
        if (action == GLFW_PRESS)
            middle_pressed_ = true;
        else
            middle_pressed_ = false;
        break;
    }

    // Dự vào action để thiết lập event type 
    MouseEventType event_type;
    switch (action) {
    case GLFW_PRESS:
        event_type = MouseEventType::DOWN;
        break;

    case GLFW_RELEASE:
        event_type = MouseEventType::UP;
        break;
    }

    // Gửi sự kiện đến hàm mouse callback 
    mouse_listener_(event_button, event_type, x_, y_);
}

// All static event handlers
// Từ các hàm pure C chuyển sang lời gọi hàm tới phương thức của object 
void GLFW::static_window_close_callback(GLFWwindow *) {
    this_->window_close_callback();
}

void GLFW::static_window_size_callback(GLFWwindow *,
        int width, int height) {
    this_->window_size_callback(width, height);
}

void GLFW::static_key_callback(GLFWwindow *,
        int key, int scancode, int action, int mods) {
    this_->key_callback(key, scancode, action, mods);
}

void GLFW::static_char_callback(GLFWwindow *,
        unsigned int code) {
    this_->char_callback(code);
}

void GLFW::static_mouse_callback(GLFWwindow *,
        int button, int action, int mods) {
    this_->mouse_callback(button, action, mods);
}

void GLFW::static_mouse_pos_callback(GLFWwindow *,
        double xpos, double ypos) {
    this_->mouse_pos_callback(xpos, ypos);
}

} // namespace tung
