#ifndef GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP
#define GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP

#include "drawable.hpp"

namespace tung {

class ImageDrawableFactory {
private:
    IImageLoader& loader_;
    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& builder_;

public:
    ImageDrawableFactory(IImageLoader& loader, 
        ITextureFactory& texture_factory,
        IVertexObjectBuilder& builder);

    IDrawablePtr new_drawable(std::string image, float height);
};

} // namespace tung

#endif