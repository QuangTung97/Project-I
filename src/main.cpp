#include <iostream>
#include <string>
#include <fstream>
#include <graphics/gl/glfw.hpp>
#include <graphics/gl/ui_shader_program.hpp>
#include <graphics/gl/vertex_object.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/gl/texture.hpp>
#include <graphics/image/png.hpp>
#include <sound/sound.hpp>
#include <chrono>

using namespace std::chrono;

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
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    tung::UIShaderProgram program{"asset/ui.vs", "asset/ui.fs"};

    auto image_loader = std::make_unique<tung::PngImageLoader>();
    auto texture_factory 
        = std::make_unique<tung::TextureFactory>();

    tung::IImagePtr image 
        = image_loader->load("asset/cute.png");
    tung::ITexturePtr texture 
        = texture_factory->create(image);

    auto builder 
        = std::make_unique<tung::VertexObjectBuilder>(program);

    builder->clear();
    builder->add_attribute("position", points, 2, 4);
    builder->add_attribute("texCoord", tex_coord, 2, 4);
    builder->add_texture(0, "image", texture);
    builder->set_indices({0, 1, 2, 0, 2, 3});
    auto object = builder->build();

    auto drawable = 
        std::make_shared<tung::Drawable>(std::move(object));

    // drawable->translate(glm::vec3(-0.2, 0, 0));

    auto group = std::make_shared<tung::DrawableGroup>();
    group->attach_drawable(drawable);

    group->rotate(3.14159 / 4, glm::vec3(0, 0, 1));

    program.set_drawable(group);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    auto sound_manager = std::make_unique<tung::SoundManager>();
    auto despacito = sound_manager->load("asset/Despacito.mp3");

    tung::ISoundPtr clone = nullptr;
    despacito->play();

    auto t0 = steady_clock::now();

    bool if_ran[3] = {false, false, false};

    auto func = [&]() {
        sound_manager->update();

        auto t1 = steady_clock::now();
        auto delta = duration_cast<milliseconds>(t1 - t0);
        if (!if_ran[0] && delta.count() > 2000) {
            despacito->pause();
            clone = despacito->clone();
            // clone->play();
            if_ran[0] = true;
        }

        if (!if_ran[1] && delta.count() > 3000) {
            despacito->resume();
            if_ran[1] = true;
        }

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
