#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <graphics/abstract/shader.h>
#include <vector>

namespace tung {

class ShaderException: public std::exception {
private:
    std::string message_;
public:
    ShaderException(std::string message) {
        message_ = std::move(message);
    }

    virtual const char *what() const noexcept override {
        return message_.c_str();
    }
};

// Base class
class ShaderProgram: public IShaderProgram {
public:
    void predraw() override;

    void postdraw() override;

    void attach_drawable(IDrawable& drawable) override;

    void detach_drawable(IDrawable& drawable) override;

protected:
    ShaderProgram();

    // input streams for read vertex shader and fragment shader
    void make_program(std::istream& vs, std::istream& fs);

    ~ShaderProgram();

private:
    // @vs: content of vertex shader
    // @fs: content of fragment shader
    void create_and_link(const char *vs, const char *fs);

    std::vector<IDrawable *> drawable_list;
    GLuint program = -1;
};

} // namespace tung

#endif
