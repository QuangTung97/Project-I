#ifndef UI_SHADER_PROGRAM
#define UI_SHADER_PROGRAM

#include "shader_program.h"

namespace tung {

class UIShaderProgram: public ShaderProgram {
public:
    UIShaderProgram(std::string vs_file, std::string fs_file);

    void draw() override;

    const std::unordered_map<std::string, int>& locations() override;
};

} // namespace tung

#endif
