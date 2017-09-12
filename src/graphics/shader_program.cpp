#include <graphics/shader_program.h>

namespace tung {

void ShaderProgram::create_and_link(const char *vs,
        const char *fs) 
{
	GLuint glvs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(glvs, 1, &vs, NULL);
	glCompileShader(glvs);

	GLuint glfs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(glfs, 1, &fs, NULL);
	glCompileShader(glfs);

    program = glCreateProgram();
    glAttachShader(program, glvs);
    glAttachShader(program, glfs);
    glLinkProgram(program);

    glDeleteShader(glvs);
    glDeleteShader(glfs);
}

ShaderProgram::ShaderProgram(GLuint vs, GLuint fs) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
}

ShaderProgram::ShaderProgram(const std::string& vs,
        const std::string& fs) 
{
    create_and_link(vs.c_str(), fs.c_str());
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    program = other.program;
    other.program = -1;
}

ShaderProgram::ShaderProgram(std::istream& vs, std::istream& fs) 
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
    glDeleteProgram(program);
}

ShaderProgram::operator GLuint() const {
    return program;
}

} // namespace tung
