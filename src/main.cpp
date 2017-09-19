#include <iostream>
#include <string>
#include <fstream>
#include <graphics/gl/glfw.h>
#include <graphics/gl/ui_shader_program.h>
#include <graphics/gl/vertex_object.h>
#include <glm/stdafx.h>
#include <glm/gtc/stdafx.h>

void draw(tung::GLFW &glfw) {
	float points[] = {
		0.0f, 0.5f,
		0.8f, -0.5f,
		-0.5f, -0.5f,
	};

    float tex_coord[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    tung::UIShaderProgram program{"asset/ui.vs", "asset/ui.fs"};

    auto builder = std::make_unique<tung::VertexObjectBuilder>();
    builder->clear();
    builder->add_attribute("position", points, 2, 3);
    builder->add_attribute("texCoord", tex_coord, 2, 3);
    auto object = builder->build(program.locations());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto func = [&object, &program]() {
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

        program.predraw();
        program.draw();
        program.postdraw();

        glm::mat4 ortho = glm::orthoLH(-1.5f, 1.5f, -1.0f, 1.0f, -10.f, 10.f);
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(0, 0.5, 0));

        auto& locations = program.locations();
        glUniformMatrix4fv(locations.at("projectionMatrix"), 1,
                GL_FALSE, glm::value_ptr(ortho));

        glUniformMatrix4fv(locations.at("modelMatrix"), 1, GL_FALSE,
                glm::value_ptr(model));

        object->bind();

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
