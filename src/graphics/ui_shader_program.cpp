#include <graphics/ui_shader_program.h>
#include <fstream>

namespace tung {

UIShaderProgram::UIShaderProgram(std::string vs_file, std::string fs_file) {
    std::ifstream vs(vs_file);
    std::ifstream fs(fs_file);
    make_program(vs, fs);
}

void UIShaderProgram::draw() {
}

std::unordered_map<std::string, int> UIShaderProgram::locations() {
    std::unordered_map<std::string, int> map;
    return map;
}

} // namespace tung
