#ifndef GRAPHICS_IMAGE_PNG
#define GRAPHICS_IMAGE_PNG

#include <graphics/abstract/image.hpp>

namespace tung {

// Kế thừa từ graphics/abstract/image.hpp
// Class chứa thông tin của một ảnh png 
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

// Kế thừa từ graphics/abstract/image.hpp
// Dùng để load ảnh dưới dạng png 
class PngImageLoader: public IImageLoader {
public:
    IImagePtr load(const std::string& filename) override;

    virtual ~PngImageLoader();
};

} // namespace tung

#endif
