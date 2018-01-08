#include <logic/actor/graphics_image.hpp>

namespace tung {
namespace actor {

const ComponentId GraphicsImage::COMPONENT_ID = ComponentId::GRAPHICS_IMAGE;

GraphicsImage::GraphicsImage(float x, float y,
    ImageDrawableFactory& factory, 
    IDrawableManagerPtr root,
    float height, const std::string& filename)
: root_{std::move(root)}
{
    // tạo một drawable chứa hình ảnh 
    drawable_ = factory.new_drawable(filename, height);
    // Di chuyển nó đến tọa độ (x, y) 
    drawable_->translate({x, y, 0});
    // Nối nó vào root 
    root_->attach_drawable(drawable_);
}

void GraphicsImage::show() {
    drawable_->show();
}

void GraphicsImage::move_to(float x, float y) {
    // Di chuyển nó đến vị trí (x, y) 
    drawable_->translate({x, y, 0});
}

void GraphicsImage::rotate(float degree) {
    float radian = degree / 180 * 3.141592654;
    // Xoay nó một góc radian theo hướng (0, 0, 1)
    drawable_->rotate(radian, {0, 0, 1});
}

void GraphicsImage::hide() {
    drawable_->hide();
}

GraphicsImage::~GraphicsImage() {
    // Xóa nó khỏi gốc drawable 
    root_->detach_drawable(drawable_);
}

} // namespace actor
} // namespace tung
