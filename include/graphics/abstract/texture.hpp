#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <memory>
#include "image.hpp"

namespace tung {

// Interface chứa thông tin một texture, phục vụ cho việc vẽ ảnh lên màn hình. 
struct ITexture {
    
    // Bind texture đó vào Shader của OpenGL.
    // @active_number: Chỉ số xác định vị trí của texture trong chương trình shader. 
    // @location: Chỉ số xác định vị trí thuộc tính trong chương trình shader. 
    virtual void bind(
            unsigned int active_number, int location) = 0;

    // Destructor
    virtual ~ITexture() {}
};

typedef std::shared_ptr<ITexture> ITexturePtr;

// Interface nhằm tạo ra các texture. 
struct ITextureFactory {
    // Create bindable texture
    // @image: con trỏ (shared_ptr) trỏ đến hình ảnh mà cần dùng để tạo texture. 
    virtual ITexturePtr create(const IImagePtr& image) = 0;

    // Destructor
    virtual ~ITextureFactory() {}
};

} // namespace tung

#endif
