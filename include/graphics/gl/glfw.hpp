#ifndef TUNG_GLFW
#define TUNG_GLFW

#include <exception>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

namespace tung {

// Exception GLFW class's errors
class glfw_exception: public std::exception {
public:
    glfw_exception(std::string error);
    virtual const char *what() const noexcept override;

private:
    std::string what_;
};

enum class MouseEventType {
    DOWN,
    UP,
    MOVE
};

enum class MouseButton {
    LEFT,
    RIGHT,
    MIDDLE
};

typedef std::function<void(MouseButton, MouseEventType, float, float)>
    MouseEventListener;

class GLFW {
public:
    // Contructor
    // @width: width of window want to create
    // @height: height of window want to create
    // @name: String that appear on the window title bar
    // @is_fullscreen: true if window is fullscreen mode (not yet supported)
    GLFW(int width, int height, const std::string& name, bool resizable = false);

    // Set callback of function would be called inside main loop
    void set_run_callback(std::function<void()> func);

    // Set callback of function would be called if window change the size 
    void set_window_size_callback(std::function<void(int, int)> func);

    // Set callback of function would be called if a key is pressed
    void set_key_callback(std::function<void(int, int, int, int)> func);

    // Set callback of function would be called if a printable key is pressed
    void set_char_callback(std::function<void(unsigned int)> func);

    // Begin main loop
    void run();

    ~GLFW();

    // Get GLFWwindow of current window, if want to have access to more information
    GLFWwindow *window() const noexcept;

private:
    GLFWwindow *window_ = nullptr;

    std::function<void()> run_callback_ = nullptr;

    // @width, @height
    std::function<void(int, int)> window_size_callback_ = nullptr;

    std::function<void(int, int, int, int)> key_callback_ = nullptr;

    std::function<void(unsigned int)> char_callback_ = nullptr;

    MouseEventListener mouse_callback_ = nullptr;

    static GLFW *this_;

    static void static_window_close_callback(GLFWwindow *);
    static void static_window_size_callback(GLFWwindow *,
            int width, int height);
    static void static_window_refresh_callback();
    static void static_key_callback(GLFWwindow *,
            int key, int scancode, int action, int mods);
    static void static_char_callback(GLFWwindow *, unsigned int code);
    static void static_mouse_callback(GLFWwindow *, int button, int action, int mods);


    void window_close_callback();
    void window_size_callback(int width, int height);
    void window_refresh_callback();
    void key_callback(int key, int scancode, int action, int mods);
    void char_callback(unsigned int code);
    void mouse_callback(int button, int action, int mods);
};

} // namespace tung

#endif // TUNG_GLFW
