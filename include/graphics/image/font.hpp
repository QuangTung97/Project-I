#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

#include "../abstract/image.hpp"
#include <vector>

namespace tung {

// Kế thừa từ graphics/abstract/image.hpp
// Class chứa thông tin để của text dwói dạng ảnh.
class FontImage: public IImage {
private:
    int width_, height_;
    // Bit depth 8
    // Format RGBA
    std::vector<unsigned char> data_;

public:
    // Constructor
    // @width: Chiều rộng của hình ảnh. 
    // @height: Chiều cao của hình ảnh. 
    // @data: Dữ liệu nhị phân của hình ảnh. 
    FontImage(int width, int height, std::vector<unsigned char> data);

    int width() const override;

    int height() const override;

    const void *data() const override;

    int color_component_count() const override;

    BitDepth bit_depth() const override;

    Format format() const override;

    // Destructor 
    virtual ~FontImage();
};

} // namespace tung

#endif
