#ifndef LOGIC_ACTOR_GRAPHICS_IMAGE_HPP
#define LOGIC_ACTOR_GRAPHICS_IMAGE_HPP

#include "component.hpp"
#include <graphics/abstract/drawable.hpp>
#include <graphics/gl/image_drawable_factory.hpp>

namespace tung {
namespace actor {

class GraphicsImage: public Component {
private:
    IDrawablePtr drawable_;
    float x_, y_;
    IDrawableManagerPtr root_;

public:
    GraphicsImage(float x, float y, 
        ImageDrawableFactory& factory, 
        IDrawableManagerPtr root,
        float height, const std::string& filename);

    void show();

    void hide();

    void move_to(float x, float y);

    ~GraphicsImage();
};

} // namespace actor
} // namespace tung

#endif