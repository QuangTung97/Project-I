#ifndef GRAPHICS_IMAGE
#define GRAPHICS_IMAGE

#include <memory>
#include <string>

namespace tung {

struct IImage {
    enum Format {
        FORMAT_RGB,
        FORMAT_RGBA,
    };

    enum BitDepth {
        BIT_DEPTH_8,
        BIT_DEPTH_16,
    };

    virtual int width() const = 0;

    virtual int height() const = 0;

    virtual const void *data() const = 0;

    virtual int color_component_count() const = 0;

    virtual BitDepth bit_depth() const = 0;

    virtual Format format() const = 0;
};

typedef std::unique_ptr<IImage> IImagePtr;

struct IImageLoader {
    virtual IImagePtr load(std::string filename) = 0;
};

typedef std::unique_ptr<IImageLoader> IImageLoaderPtr;

} // namespace tung

#endif
