#ifndef GRAPHICS_GL_SPRITE_FACTORY_HPP
#define GRAPHICS_GL_SPRITE_FACTORY_HPP

#include "sprite_drawable.hpp"
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

// Class nhằm để tạo ra các Sprite Drawable
class SpriteFactory {
private:
    IGraphicsAssetManager& asset_manager_;
    IVertexObjectBuilder& builder_;

public:
    // constructor
    // @asset_manager_: Bộ quản lý tài nguyên. 
    // @builder: Builder để build vertex object. 
    SpriteFactory(IGraphicsAssetManager& asset_manager_,
        IVertexObjectBuilder& builder);

    // @image: Đường dẫn tới ảnh chứa file sprite. 
    // @rows: Số hàng của file ảnh sprite đó. 
    // @cols: Sô cột của file ảnh sprite đó. 
    // @height: chiều cao sẽ được vẽ lên màn hình. 
    // Return: Con trỏ tới Drawable được tạo
    std::shared_ptr<SpriteDrawable> new_sprite(
        const std::string& image, int rows, int cols, float height);

private:
    // @ITexturePtr: Con trỏ trỏ tới texture. 
    // @image_width: Chiều rộng của hình ảnh. 
    // @image_height: Chiều cao của hình ảnh. 
    // @rows: Số hàng của file ảnh sprite đó. 
    // @cols: Sô cột của file ảnh sprite đó. 
    // @height: chiều cao sẽ được vẽ lên màn hình. 
    // Return: Con trỏ trỏ tới Drawable được tạo 
    // Hàm phụ trợ cho new_sprite
    std::shared_ptr<SpriteDrawable> create_sprite(
        ITexturePtr, int image_width, int image_height, 
        int rows, int cols, float height);
};

} // namespace tung

#endif