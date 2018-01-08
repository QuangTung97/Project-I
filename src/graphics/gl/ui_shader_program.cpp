#include <graphics/gl/ui_shader_program.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tung {

UIShaderProgram::UIShaderProgram(std::string vs_file, std::string fs_file) {
    // Tạo stream từ 2 file 
    std::ifstream vs(vs_file);
    std::ifstream fs(fs_file);
    // Tạo chương trình shader 
    make_program(vs, fs);
}

void UIShaderProgram::predraw(float width, float height) {
    // Gọi hàm của super class 
    ShaderProgram::predraw(width, height);
    
    // Tính toán ma trận chiếu trực giao 
    glm::mat4 ortho = glm::orthoLH(
            0.0f, width, height, 0.0f, -1.0f, 1.0f);

    // Update gía trị ma trận chiếu đó cho OpenGL 
    glUniformMatrix4fv(locations_.at("projectionMatrix"), 1,
            GL_FALSE, glm::value_ptr(ortho));

    // Hủy depth test 
    glDisable(GL_DEPTH_TEST);
}

void UIShaderProgram::postdraw() {
    // Kích hoạt loại depth test 
    glEnable(GL_DEPTH_TEST);
}

const std::unordered_map<std::string, int> &UIShaderProgram::locations() {
    // Nếu danh sách các vị trí đã có 
    // Thì trả về luôn 
    if (locations_.size() != 0)
        return locations_;

    locations_["image"] = 
        glGetUniformLocation(program_, "image");
    locations_["projectionMatrix"] = 
        glGetUniformLocation(program_, "projectionMatrix");
    locations_["modelMatrix"] = 
        glGetUniformLocation(program_, "modelMatrix");
    locations_["position"] = 
        glGetAttribLocation(program_, "position");
    locations_["texCoord"] = 
        glGetAttribLocation(program_, "texCoord");
    return locations_;
}

} // namespace tung
