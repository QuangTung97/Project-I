#include <graphics/gl/glfw.hpp>
#include <exception>
#include <iostream>

namespace tung {

glfw_exception::glfw_exception(std::string error)
    : what_{std::move(error)} {}

const char *glfw_exception::what() const noexcept {
    return what_.c_str();
}

GLFW *GLFW::this_ = nullptr;

GLFW::GLFW(int width, int height, 
        const std::string& name, bool resizable) {
    this_ = this;
    if (!::glfwInit()) {
        this_ = nullptr;
        throw glfw_exception("Can't init");
    }

    if (!resizable) 
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = ::glfwCreateWindow(width, height, 
            name.c_str(), nullptr, NULL);

    if (!window_) {
        ::glfwTerminate();
        this_ = nullptr;
        throw glfw_exception("Can't create window");
    }

	::glfwMakeContextCurrent(window_);

    ::glfwSetWindowCloseCallback(window_, 
            static_window_close_callback);
    ::glfwSetWindowSizeCallback(window_,
            static_window_size_callback);
    ::glfwSetKeyCallback(window_, static_key_callback);
    ::glfwSetCharCallback(window_, static_char_callback);

	::glewExperimental = GL_TRUE;
	::glewInit();
}

void GLFW::set_run_callback(std::function<void()> func) {
    run_callback_ = std::move(func);
}

void GLFW::set_window_size_callback(
        std::function<void(int, int)> func) {
    window_size_callback_ = std::move(func);
}

void GLFW::set_key_callback(
        std::function<void(int, int, int, int)> func) {
    key_callback_ = std::move(func);
}

void GLFW::set_char_callback(
        std::function<void(unsigned int)> func) {
    char_callback_ = std::move(func);
}

void GLFW::run() {
    glfwSwapInterval(30);
    while (!::glfwWindowShouldClose(window_)) {
        if (run_callback_)
            run_callback_();
        ::glfwPollEvents();
        ::glfwSwapBuffers(window_);
    }
}

GLFWwindow *GLFW::window() const noexcept {
    return window_;
}

GLFW::~GLFW() {
    ::glfwDestroyWindow(window_);
    window_ = nullptr;
    ::glfwTerminate();
    this_ = nullptr;
}

void GLFW::window_close_callback() {
}

void GLFW::window_size_callback(int width, int height) {
    if (window_size_callback_)
        window_size_callback_(width, height);
}

void GLFW::key_callback(int key, int scancode, 
        int action, int mods) {
    if (key_callback_)
        key_callback_(key, scancode, action, mods);
}

void GLFW::char_callback(unsigned int code) {
    if (char_callback_)
        char_callback_(code);
}

void GLFW::mouse_callback(int button, int action, int mods) {
    if (mouse_callback_ == nullptr)
        return;

    MouseEventType event_type;
    switch (action) {
    case GLFW_PRESS:
        event_type = MouseEventType::DOWN;
        break;

    case GLFW_RELEASE:
        event_type = MouseEventType::UP;
        break;

    default:
        break;
    }

    double xpos, ypos;
    ::glfwGetCursorPos(window_, &xpos, &ypos);
}

// All static event handlers
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

} // namespace tung
