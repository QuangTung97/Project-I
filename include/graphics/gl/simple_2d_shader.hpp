#ifndef GRAPHICS_GL_SIMPLE_2D_SHADER_HPP
#define GRAPHICS_GL_SIMPLE_2D_SHADER_HPP

#include "shader_program.hpp"

namespace tung {

// Kế thừa từ shader_program.hpp
class Simple2DShader: public ShaderProgram {
public:
    // Constructor
    // @vs_file: Đường dẫn đến vertex shader
    // @fs_file: Đường dẫn đến fragment shader
    Simple2DShader(std::string vs_file, std::string fs_file);

    void predraw(float width, float height) override;

    void postdraw() override;

    const std::unordered_map<std::string, int>& locations() override;
};

} // namespace tung

#endif