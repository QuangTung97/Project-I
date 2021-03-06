#include <graphics/gl/texture.hpp>
#include <GL/glew.h>

namespace tung {

// Texture
void Texture::bind(unsigned int active_number, int location) {
    glActiveTexture(GL_TEXTURE0 + active_number);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glUniform1i(location, active_number);
}

Texture::~Texture() {
    // Xóa texture trong GPU 
    glDeleteTextures(1, &texture_);
}

// Texture Factory
TextureFactory::TextureFactory() {}

ITexturePtr TextureFactory::create(
        const IImagePtr& image)
{
    // Tạo một object texture 
    auto texture = std::make_shared<Texture>();

    // Sinh một vùng nhớ lưu trữ texture 
    glGenTextures(1, &texture->texture_);
    // Thiết lập texture đó lưu trữ ảnh 2D
    glBindTexture(GL_TEXTURE_2D, texture->texture_);

    // Định dạng và kiểu của texture 
    int format;
    if (image->format() == IImage::FORMAT_RGB)
        format = GL_RGB;
    else if (image->format() == IImage::FORMAT_RGBA)
        format = GL_RGBA;
    else
        return nullptr;

    int type;
    if (image->bit_depth() == IImage::BIT_DEPTH_8)
        type = GL_UNSIGNED_BYTE;
    else if (image->bit_depth() == IImage::BIT_DEPTH_16)
        type = GL_UNSIGNED_SHORT;
    else 
        return nullptr;

    // Truyền dữ liệu cho texture đó 
    glTexImage2D(GL_TEXTURE_2D, 
            0, // level of detail, 0 if not has
            image->color_component_count(), 
            image->width(),
            image->height(),
            0, // border, this value must be 0
            format,
            type,
            image->data());

    // Thiết lập phương thức nội suy cho các pixel trên texture 
    glTexParameteri(GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return texture;
}

TextureFactory::~TextureFactory() {}

} // namespace tung
