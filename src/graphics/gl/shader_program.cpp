#include <graphics/gl/shader_program.h>
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
        glGetShaderiv(glvs, GL_INFO_LOG_LENGTH, &max_len);

        std::vector<GLchar> error_log(max_len);
        // Copy error message to error_log
        glGetShaderInfoLog(glvs, max_len, &max_len, error_log.data());

        std::string error_string(error_log.begin(), error_log.end());

        glDeleteShader(glvs);
        throw ShaderException(error_string);
    }

    // Create and compile fragment shader
	GLuint glfs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(glfs, 1, &fs, NULL);
    glCompileShader(glfs);

    glGetShaderiv(glfs, GL_COMPILE_STATUS, &is_compiled);
    // Error happened while compile fragment shader
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

    glDeleteShader(glvs);
    glDeleteShader(glfs);
}

ShaderProgram::ShaderProgram() {}


void ShaderProgram::make_program(std::istream& vs, std::istream& fs) 
{
    std::string line;
    std::string vs_string;
    std::string fs_string;
    while (std::getline(vs, line)) {
        line += '\n';
        vs_string += line;
    }
    while (std::getline(fs, line)) {
        line += '\n';
        fs_string += line;
    }

    create_and_link(vs_string.c_str(), fs_string.c_str());
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_);
}

void ShaderProgram::predraw() {
    glUseProgram(this->program_);
}

void ShaderProgram::postdraw() {
}

void ShaderProgram::attach_drawable(IDrawable& drawable) {
    drawable_list.push_back(&drawable);
    drawable.on_attach_drawable(*this);
}

void ShaderProgram::detach_drawable(IDrawable& drawable) {
    drawable.on_detach_drawable(*this);
    drawable_list.erase(
            std::remove(drawable_list.begin(), drawable_list.end(), &drawable),
            drawable_list.end()
    );
}

} // namespace tung
