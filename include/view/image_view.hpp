#ifndef VIEW_IMAGE_VIEW_HPP
#define VIEW_IMAGE_VIEW_HPP

#include <view/view.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

// Chứa thông tin để vẽ một View chứa hình ảnh
class ImageView: public View {
protected:
    static IVertexObjectBuilder *builder_;
    static IGraphicsAssetManager *asset_manager_;
    ITexturePtr texture_;
    std::string filename_;

    // Cập nhật lại biến drawable_ để chứa những thông tin mới. 
    void validate();

public:
    // Constructor 
    // @x, @y: Tạo độ của view, tính theo góc trên bên trái (đơn vị pixel).
    // @width, @height: Chiều rộng và chiều cao của view. 
    // @image_file: Đường dẫn đến file hình ảnh. 
    ImageView(float x, float y, float width, float height, 
            const std::string& image_file);

    // Thiết lập vertex object builder cần thiết để hiển thị được ảnh.
    // @builder: Một vertex object builder  
    static void set_vertex_object_builder(IVertexObjectBuilder& builder) {
        builder_ = &builder;
    }

    // Thiết lập asset manager để load được ảnh từ thư mục assets. 
    // @manager: một asset manager. 
    static void set_asset_manager(IGraphicsAssetManager& manager) {
        asset_manager_ = &manager;
    }

    void set_size(float, float) override;

    // Thiết lập đường dẫn đến file ảnh khác. 
    // @filename: Đường dẫn đến file ảnh 
    void set_image(const std::string& filename);

    // Destructor 
    virtual ~ImageView() {}
};

} // namespace tung

#endif
