#include <iostream>
#include <string>
#include <fstream>
#include <graphics/gl/glfw.h>
#include <graphics/gl/ui_shader_program.h>
#include <graphics/gl/vertex_object.h>
#include <graphics/gl/drawable.h>
#include <glm/stdafx.h>
#include <glm/gtc/stdafx.h>

void draw(tung::GLFW &glfw) {
	float points[] = {
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
	};

    float tex_coord[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    tung::UIShaderProgram program{"asset/ui.vs", "asset/ui.fs"};

    auto builder 
        = std::make_unique<tung::VertexObjectBuilder>(program);

    builder->clear();
    builder->add_attribute("position", points, 2, 4);
    builder->add_attribute("texCoord", tex_coord, 2, 4);
    builder->set_indices({0, 1, 2, 0, 2, 3});
    auto object = builder->build();

    auto drawable = std::make_shared<tung::Drawable>(std::move(object));
    drawable->translate(glm::vec3(-0.5, 0, 0));

    auto group = std::make_shared<tung::DrawableGroup>();
    group->attach_drawable(drawable);

    group->rotate(3.14159 / 4, glm::vec3(0, 0, 1));

    program.set_drawable(group);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto func = [&program]() {
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

        program.predraw(640, 480);
        program.draw();
        program.postdraw();
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
