#include <iostream>
#include <string>
#include <fstream>
#include <graphics/glfw.h>
#include <graphics/shader_program.h>

void draw(tung::GLFW &glfw) {
	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

    // vertex buffer object
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, 
			GL_STATIC_DRAW);

    // vertex array object
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    std::ifstream vs{"asset/ui.vs"};
    std::ifstream fs{"asset/ui.fs"};
    tung::ShaderProgram program{vs, fs};

    auto func = [&vao, &program]() {
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);

		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);
    };

    glfw.set_run_callback(func);
    glfw.run();
}

int main() {
    tung::GLFW glfw(640, 480, "Tung");

    // tung::OpenGLInfo info;
    // std::cout << info << std::endl;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    auto func = [](unsigned int code) {
        std::cout << code << std::endl;
    }; 
    glfw.set_char_callback(func);

	draw(glfw);
	return 0;
}
