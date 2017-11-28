#ifndef GRAPHICS_ABSTRACT_GRAPHICS_ASSET_MANAGER_HPP
#define GRAPHICS_ABSTRACT_GRAPHICS_ASSET_MANAGER_HPP

#include "texture.hpp"

namespace tung {

// Interface quản lý các tài nguyên của game.
struct IGraphicsAssetManager {
    // @filename: Đường dẫn đến file tài nguyên đó 
    virtual IImagePtr get_image(const std::string& filename) = 0;

    // @filename: Đường dẫn đến file tài nguyên đó 
    virtual ITexturePtr get_texture(const std::string& filename) = 0;

    // Destructor
    virtual ~IGraphicsAssetManager() {}
};

} // namespace tung

#endif