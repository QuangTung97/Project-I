#ifndef GRAPHICS_GL_SIMPLE_2D_SHADER_HPP
#define GRAPHICS_GL_SIMPLE_2D_SHADER_HPP

#include "shader_program.hpp"

namespace tung {

class Simple2DShader: public ShaderProgram {
public:
    Simple2DShader(std::string vs_file, std::string fs_file);

    void predraw(float width, float height) override;

    void postdraw() override;

    const std::unordered_map<std::string, int>& locations() override;
};

} // namespace tung

#endif