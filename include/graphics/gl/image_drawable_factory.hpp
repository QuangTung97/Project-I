#ifndef GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP
#define GRAPHICS_GL_IMAGE_DRAWABLE_FACTORY_HPP

#include "drawable.hpp"
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

// Class nhằm để sinh ra một drawable mà chứa sẵn hình ảnh. 
class ImageDrawableFactory {
private:
    IGraphicsAssetManager& asset_manager_;
    IVertexObjectBuilder& builder_;

public:
    // @asset_manager: Bộ quản lý tài nguyên 
    // @builder: Builder để build Vertex Object
    ImageDrawableFactory(
        IGraphicsAssetManager& asset_manager,
        IVertexObjectBuilder& builder);

    // @image: Đường dẫn đến file ảnh. 
    // @height: Chiều cao của ảnh sẽ được vẽ lên màn hình. 
    // (Chiều rộng sẽ được tính nhờ kích thước ảnh)
    // Return: Con trỏ trỏ đến drawable đã được tạo. 
    IDrawablePtr new_drawable(const std::string& image, float height);
};

} // namespace tung

#endif