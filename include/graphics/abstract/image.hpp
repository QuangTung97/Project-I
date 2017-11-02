#ifndef GRAPHICS_IMAGE
#define GRAPHICS_IMAGE

#include <memory>
#include <string>
#include <exception>

namespace tung {

class ImageException: public std::exception {
private:
    std::string what_;

public:
    ImageException(std::string what): what_{what} {}

    const char *what() const noexcept override {
        return what_.c_str();
    }
};

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

    virtual ~IImage() {}
};

typedef std::shared_ptr<IImage> IImagePtr;

struct IImageLoader {
    virtual IImagePtr load(const std::string& filename) = 0;

    virtual ~IImageLoader() {}
};

} // namespace tung

#endif
