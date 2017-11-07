#include <logic/actor/graphics_image.hpp>

namespace tung {
namespace actor {

GraphicsImage::GraphicsImage(float x, float y,
    ImageDrawableFactory& factory, 
    IDrawableManagerPtr root,
    float height, const std::string& filename)
: x_{x}, y_{y}, root_{std::move(root)}
{
    drawable_ = factory.new_drawable(filename, height);
    drawable_->translate({x_, y_, 0});
    root_->attach_drawable(drawable_);
}

void GraphicsImage::show() {
    drawable_->show();
}

void GraphicsImage::move_to(float x, float y) {
    x_ = x;
    y_ = y;
    drawable_->translate({x_, y_, 0});
}

void GraphicsImage::hide() {
    drawable_->hide();
}

GraphicsImage::~GraphicsImage() {
    root_->detach_drawable(drawable_);
}

} // namespace actor
} // namespace tung