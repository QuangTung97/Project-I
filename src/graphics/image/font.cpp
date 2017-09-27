#include <graphics/image/font.h>

namespace tung {

// Font Image
FontImage::FontImage() {
}

int FontImage::width() const {
    return width_;
}

int FontImage::height() const {
    return height_;
}

const void *FontImage::data() const {
    return data_;
}

int FontImage::color_component_count() const {
    return 4;
}

IImage::BitDepth FontImage::bit_depth() const {
    return IImage::BIT_DEPTH_8;
}

IImage::Format FontImage::format() const {
    return IImage::FORMAT_RGBA;
}

FontImage::~FontImage() {
    ::free(data_);
}

} // namespace tung
