#include <graphics/gl/simple_2d_shader.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tung {

Simple2DShader::Simple2DShader(std::string vs_file, std::string fs_file) {
    // Tạo stream từ 2 tên file 
    std::ifstream vs(vs_file);
    std::ifstream fs(fs_file);
    // Tạo chương trình shader 
    make_program(vs, fs);
}

void Simple2DShader::predraw(float width, float height) {
    // Gọi hàm của super class 
    ShaderProgram::predraw(width, height);

    // Tính toán tỉ lệ màn hình 
    float ratio = width / height;
    
    // Tính toán ma trận chiếu trực giao 
    glm::mat4 ortho = glm::orthoLH(
            -ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

    // Gán giá trị ma trận chiếu trực giao vào chương trình (trên GPU) 
    glUniformMatrix4fv(locations_.at("projectionMatrix"), 1,
            GL_FALSE, glm::value_ptr(ortho));

    // Hủy kích hoạt depth test 
    glDisable(GL_DEPTH_TEST);
}

void Simple2DShader::postdraw() {
    // kích hoạt depth test 
    glEnable(GL_DEPTH_TEST);
}

const std::unordered_map<std::string, int> &Simple2DShader::locations() {
    // Nếu locations_ đã chứa dữ liệu
    // thì trả về luôn 
    if (locations_.size() != 0)
        return locations_;

    // Lấy vị trí từ chương trình shader 
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
