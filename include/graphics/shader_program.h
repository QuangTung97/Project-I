#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <iostream>
#include <string>
#include <GL/glew.h>

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

class ShaderProgram {
public:
    // @vs: precompile vertex shader
    // @fs: precompile fragment shader
    ShaderProgram(GLuint vs, GLuint fs);

    // @vs: content of vertex shader
    // @fs: content of fragment shader
    ShaderProgram(const std::string& vs,
                const std::string& fs);

    ShaderProgram(const ShaderProgram&) = delete;

    // Move constructor
    ShaderProgram(ShaderProgram&& other) noexcept;

    // input streams for read vertex shader and fragment shader
    ShaderProgram(std::istream& vs, std::istream& fs);

    ~ShaderProgram();

    operator GLuint () const;

private:
    // @vs: content of vertex shader
    // @fs: content of fragment shader
    void create_and_link(const char *vs, const char *fs);
    GLuint program = -1;
};

} // namespace tung

#endif
