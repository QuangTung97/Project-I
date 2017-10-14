#ifndef UI_SHADER_PROGRAM
#define UI_SHADER_PROGRAM

#include "shader_program.hpp"

namespace tung {

class UIShaderProgram: public ShaderProgram {
public:
    UIShaderProgram(std::string vs_file, std::string fs_file);

    void predraw(float width, float height) override;

    void postdraw() override;

    const std::unordered_map<std::string, int>& locations() override;
};

} // namespace tung

#endif
