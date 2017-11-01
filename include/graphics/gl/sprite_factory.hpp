#ifndef GRAPHICS_GL_SPRITE_FACTORY_HPP
#define GRAPHICS_GL_SPRITE_FACTORY_HPP

#include "sprite_drawable.hpp"
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

class SpriteFactory {
private:
    IGraphicsAssetManager& asset_manager_;
    IVertexObjectBuilder& builder_;

public:
    SpriteFactory(IGraphicsAssetManager& asset_manager_,
        IVertexObjectBuilder& builder);

    std::shared_ptr<SpriteDrawable> new_sprite(
        const std::string& image, int rows, int cols, float height);

private:
    std::shared_ptr<SpriteDrawable> create_sprite(
        ITexturePtr, int image_width, int image_height, 
        int rows, int cols, float height);
};

} // namespace tung

#endif