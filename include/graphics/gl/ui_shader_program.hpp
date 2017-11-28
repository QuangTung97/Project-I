#ifndef UI_SHADER_PROGRAM
#define UI_SHADER_PROGRAM

#include "shader_program.hpp"

namespace tung {

// Kế thừa từ shader_program.hpp
class UIShaderProgram: public ShaderProgram {
public:
    // @vs_file: Đường dẫn đến file chứa code của vertex shader
    // @fs_file: Đường dẫn đến file chứa code của fragment shader
    UIShaderProgram(std::string vs_file, std::string fs_file);

    void predraw(float width, float height) override;

    void postdraw() override;

    const std::unordered_map<std::string, int>& locations() override;
};

} // namespace tung

#endif
