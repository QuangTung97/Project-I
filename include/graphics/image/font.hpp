#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

#include "../abstract/image.hpp"
#include <vector>

namespace tung {

class FontImage: public IImage {
private:
    int width_, height_;
    // Bit depth 8
    // Format RGBA
    std::vector<unsigned char> data_;

public:
    FontImage(int width, int height, std::vector<unsigned char> data);

    int width() const override;

    int height() const override;

    const void *data() const override;

    int color_component_count() const override;

    BitDepth bit_depth() const override;

    Format format() const override;

    virtual ~FontImage();
};

} // namespace tung

#endif
