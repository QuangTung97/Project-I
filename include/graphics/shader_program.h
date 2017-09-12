#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <iostream>
#include <GL/glew.h>

namespace tung {

class ShaderProgram {
public:
    ShaderProgram(GLuint vs, GLuint fs);

    ShaderProgram(const std::string& vs,
                const std::string& fs);

    ShaderProgram(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;

    ShaderProgram(std::istream& vs, std::istream& fs);

    ~ShaderProgram();

    operator GLuint () const;

private:
    void create_and_link(const char *vs, const char *fs);
    GLuint program = -1;
};

} // namespace tung

#endif
