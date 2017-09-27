#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

#include "../abstract/image.h"

namespace tung {

class FontImage: public IImage {
private:
    int width_, height_;
    // Bit depth 8
    // Format RGBA
    void *data_;

public:
    FontImage();

    int width() const override;

    int height() const override;

    const void *data() const override;

    int color_component_count() const override;

    BitDepth bit_depth() const override;

    Format format() const override;

    virtual ~FontImage();
};

class FontImageFactory {
public:
    IImagePtr create(
            float red, float green, float blue, 
            const std::string& font,
            const std::string& str);

};

} // namespace tung

#endif
