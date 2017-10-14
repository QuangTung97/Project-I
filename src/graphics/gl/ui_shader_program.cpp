#include <graphics/gl/ui_shader_program.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tung {

UIShaderProgram::UIShaderProgram(std::string vs_file, std::string fs_file) {
    std::ifstream vs(vs_file);
    std::ifstream fs(fs_file);
    make_program(vs, fs);
}

void UIShaderProgram::predraw(float width, float height) {
    ShaderProgram::predraw(width, height);
    
    glm::mat4 ortho = glm::orthoLH(
            0.0f, width, height, 0.0f, -1.0f, 1.0f);

    glUniformMatrix4fv(locations_.at("projectionMatrix"), 1,
            GL_FALSE, glm::value_ptr(ortho));

    glDisable(GL_DEPTH_TEST);
}

void UIShaderProgram::postdraw() {
    glEnable(GL_DEPTH_TEST);
}

const std::unordered_map<std::string, int> &UIShaderProgram::locations() {
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
