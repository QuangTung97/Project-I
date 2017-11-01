#ifndef GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP
#define GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP

#include "drawable.hpp"
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

class ImageDrawableFactory {
private:
    IGraphicsAssetManager& asset_manager_;
    IVertexObjectBuilder& builder_;

public:
    ImageDrawableFactory(
        IGraphicsAssetManager& asset_manager,
        IVertexObjectBuilder& builder);

    IDrawablePtr new_drawable(const std::string& image, float height);
};

} // namespace tung

#endif