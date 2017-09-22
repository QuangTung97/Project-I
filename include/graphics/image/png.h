#ifndef GRAPHICS_IMAGE_PNG
#define GRAPHICS_IMAGE_PNG

#include <graphics/abstract/image.h>

namespace tung {

class PngImage: public IImage {
private:
    int width_, height_;
    BitDepth bit_depth_;
    void *data_;
    Format format_;
    friend class PngImageLoader;

public:
    PngImage();

    int width() const override;

    int height() const override;

    const void *data() const override;

    int color_component_count() const override;

    BitDepth bit_depth() const override;

    Format format() const override;

    virtual ~PngImage();
};

class PngImageLoader: public IImageLoader {
public:
    IImagePtr load(const std::string& filename) override;

    virtual ~PngImageLoader();
};

} // namespace tung

#endif
