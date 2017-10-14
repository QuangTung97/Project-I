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
#include <view/image_view.hpp>

void draw(tung::GLFW &glfw) {
    tung::UIShaderProgram program{"asset/ui.vs", "asset/ui.fs"};

    auto image_loader = std::make_unique<tung::PngImageLoader>();
    auto texture_factory 
        = std::make_unique<tung::TextureFactory>();
    auto builder 
        = std::make_unique<tung::VertexObjectBuilder>(program);

    tung::ImageView::set_vertex_object_builder(*builder);
    tung::ImageView::set_texture_factory(*texture_factory);

    auto image = image_loader->load("asset/cute.png");
    auto background = image_loader->load("asset/llvm.png");

    auto background_view = std::make_shared<tung::ImageView>(
            0, 0, 640, 480, background);
    auto image_view = std::make_shared<tung::ImageView>(
            50, 50, 100, 100, image);

    auto window = std::make_shared<tung::ViewGroup>(
            0, 0, 640, 480);

    window->add_view(background_view);
    window->add_view(image_view);

    program.set_drawable(window->get_drawable());

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
            image_view->set_top_left(100, 100);
            image_view->set_size(200, 200);
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
