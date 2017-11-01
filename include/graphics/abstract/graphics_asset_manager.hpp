#ifndef GRAPHICS_ABSTRACT_GRAPHICS_ASSET_MANAGER_HPP
#define GRAPHICS_ABSTRACT_GRAPHICS_ASSET_MANAGER_HPP

#include "texture.hpp"

namespace tung {

struct IGraphicsAssetManager {
    virtual IImagePtr get_image(const std::string& filename) = 0;

    virtual ITexturePtr get_texture(const std::string& filename) = 0;

    virtual ~IGraphicsAssetManager() {}
};

} // namespace tung

#endif