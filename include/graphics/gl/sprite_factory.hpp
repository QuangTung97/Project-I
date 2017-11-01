#ifndef GRAPHICS_GL_SPRITE_FACTORY_HPP
#define GRAPHICS_GL_SPRITE_FACTORY_HPP

#include "sprite_drawable.hpp"

namespace tung {

class SpriteFactory {
private:
    IImageLoader& loader_;
    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& builder_;

public:
    SpriteFactory(IImageLoader& loader, 
        ITextureFactory& texture_factory,
        IVertexObjectBuilder& builder);

    std::shared_ptr<SpriteDrawable> new_sprite(
        std::string image, int rows, int cols, float height);

    std::shared_ptr<SpriteDrawable> new_sprite(
        ITexturePtr texture, int image_width, int image_height,
        int rows, int cols, float height);

private:
    std::shared_ptr<SpriteDrawable> create_sprite(
        ITexturePtr, int image_width, int image_height, 
        int rows, int cols, float height);
};

} // namespace tung

#endif