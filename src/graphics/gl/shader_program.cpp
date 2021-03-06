#include <graphics/gl/shader_program.hpp>
#include <vector>
#include <algorithm>

namespace tung {

void ShaderProgram::create_and_link(const char *vs,
        const char *fs) 
{
    int is_compiled;
    // Create and compile vertex shader
	GLuint glvs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(glvs, 1, &vs, NULL);
	glCompileShader(glvs);

    glGetShaderiv(glvs, GL_COMPILE_STATUS, &is_compiled);
    // Error happened while compile fragment shader
	if (is_compiled == GL_FALSE) {
        GLint max_len = 0;
        // Thấy giá trị chiều dài của message lỗi 
        glGetShaderiv(glvs, GL_INFO_LOG_LENGTH, &max_len);

        // Tạo một mảng để chứa message lỗi 
        std::vector<GLchar> error_log(max_len);
        // Copy error message to error_log
        glGetShaderInfoLog(glvs, max_len, &max_len, error_log.data());

        // Tạo một xâu lỗi 
        std::string error_string(error_log.begin(), error_log.end());

        // Xóa chương trình vertex shader 
        glDeleteShader(glvs);
        throw ShaderException(error_string);
    }

    // Create and compile fragment shader
	GLuint glfs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(glfs, 1, &fs, NULL);
    glCompileShader(glfs);

    glGetShaderiv(glfs, GL_COMPILE_STATUS, &is_compiled);
    // Error happened while compile fragment shader
    // Tương tự với trên 
	if (is_compiled == GL_FALSE) {
        GLint max_len = 0;
        glGetShaderiv(glfs, GL_INFO_LOG_LENGTH, &max_len);

        std::vector<GLchar> error_log(max_len);
        glGetShaderInfoLog(glfs, max_len, &max_len, error_log.data());
        glDeleteShader(glfs);
        std::string error_string(error_log.begin(), error_log.end());
        throw ShaderException(error_string);
    }

    // Link vertex shader and fragment shader to form a program
    program_ = glCreateProgram();
    glAttachShader(program_, glvs);
    glAttachShader(program_, glfs);
    glLinkProgram(program_);

    int isLinked;
    glGetProgramiv(program_, GL_LINK_STATUS, (int *)&isLinked);
    // Error happned while linking
    // Tương tự với trên 
    if (isLinked == GL_FALSE) {
        int max_len;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &max_len);
        std::vector<char> info_log(max_len);
        // Copy error message to info_log
        glGetProgramInfoLog(program_, max_len, &max_len, info_log.data());
        std::string error_string(info_log.begin(), info_log.end());

        // We don't need anymore
        glDeleteProgram(program_);
        glDeleteShader(glvs);
        glDeleteShader(glfs);
        throw ShaderException(error_string);
    }

    // Xóa các vertex shader và fragment shader 
    glDeleteShader(glvs);
    glDeleteShader(glfs);
}

ShaderProgram::ShaderProgram() {
    // Khởi tạo bằng việc push ma trận đơn vị vào stack 
    model_matrix_stack_.push_back(glm::mat4(1.0));
}

void ShaderProgram::make_program(std::istream& vs, std::istream& fs) 
{
    std::string line;
    std::string vs_string;
    std::string fs_string;
    // Đọc từng dòng 
    while (std::getline(vs, line)) {
        line += '\n';
        // nối nó vào xâu vs_string 
        vs_string += line;
    }
    while (std::getline(fs, line)) {
        line += '\n';
        // nối nó vào xâu fs_string 
        fs_string += line;
    }

    // Tạo chương trình shader từ 2 xâu đó 
    create_and_link(vs_string.c_str(), fs_string.c_str());
}

ShaderProgram::~ShaderProgram() {
    // Xóa chương trình shader 
    glDeleteProgram(program_);
}

void ShaderProgram::predraw(float, float) {
    // Sử dụng chương trình shader này để vẽ 
    glUseProgram(this->program_);
}

void ShaderProgram::draw() {
    // Nếu gốc drawable tồn tại 
    // Thì gọi hàm on_draw 
    if (drawable_)
        drawable_->on_draw(*this);
}

void ShaderProgram::postdraw() {
}

void ShaderProgram::set_drawable(const IDrawablePtr& drawable) {
    drawable_ = drawable;
}

std::vector<glm::mat4>& ShaderProgram::model_matrix_stack() {
    return model_matrix_stack_;
}

} // namespace tung
