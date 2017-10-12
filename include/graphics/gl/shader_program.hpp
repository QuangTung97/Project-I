#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <graphics/abstract/shader_program.hpp>
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
    void predraw(float width, float height) override;

    void draw() override;

    void postdraw() override;

    void set_drawable(const IDrawablePtr& drawable) override;

    std::vector<glm::mat4>& model_matrix_stack() override;

protected:
    std::unordered_map<std::string, int> locations_;
    GLuint program_ = -1;

protected:
    ShaderProgram();

    // input streams for read vertex shader and fragment shader
    void make_program(std::istream& vs, std::istream& fs);

    ~ShaderProgram();

private:
    // @vs: content of vertex shader
    // @fs: content of fragment shader
    void create_and_link(const char *vs, const char *fs);

    IDrawablePtr drawable_;
    std::vector<glm::mat4> model_matrix_stack_;
};

} // namespace tung

#endif
