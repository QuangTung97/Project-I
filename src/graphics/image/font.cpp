#include <graphics/image/font.hpp>

namespace tung {

// Font Image
FontImage::FontImage(int width, int height, std::vector<unsigned char> data)
: width_{width}, height_{height}, data_{std::move(data)} 
{}

int FontImage::width() const {
    return width_;
}

int FontImage::height() const {
    return height_;
}

const void *FontImage::data() const {
    return data_.data();
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
}

} // namespace tung
