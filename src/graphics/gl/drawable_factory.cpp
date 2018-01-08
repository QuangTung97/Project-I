#include <graphics/gl/image_drawable_factory.hpp>
#include <graphics/gl/sprite_factory.hpp>

#include <iostream>

namespace tung {

// Khởi tạo các tham chiếu đến Graphics Asset Manager,
// Vertex Object Builder
SpriteFactory::SpriteFactory(IGraphicsAssetManager& asset_manager,
        IVertexObjectBuilder& builder)
    : asset_manager_{asset_manager}, builder_{builder}
{}

std::shared_ptr<SpriteDrawable> SpriteFactory::create_sprite(
    ITexturePtr texture, int image_width, int image_height, 
    int rows, int cols, float height) 
{
    // Khởi tạo một SpriteDrawable 
    auto sprite = std::make_shared<SpriteDrawable>();

    // Tính toán giá trị chiều rộng sẽ vẽ lên màn hình 
    // Nhờ giá trị chiều vào và chiều rộng + chiều cao của ảnh 
    float width = height * image_width / (float)image_height * rows / (float)cols;

    // Tứ giác sẽ vẽ lên màn hình 
    float points[] = {
        -width / 2, height / 2,
        -width / 2, -height / 2,
        width / 2, -height / 2,
        width / 2, height / 2
    };

    // Duyệt lần lượt qua từng ảnh con trong ảnh sprite 
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // Tính toán tọa độ để hiển thị texture 
            // Bao gồm vị trí (x, y) và chiều rộng, chiều cao 
            float texture_width = 1.0f / cols;
            float texture_height = 1.0f / rows;
            float x = (float)col / cols;
            float y = (float)row / rows;

            // Do tọa độ của texture sử dụng là bắt đầu từ góc 
            // dưới bên trái 
            // Nên phải tính thêm 2 giá trị 
            float bottom = 1.0f - y - texture_height;
            float left = x;

            // 4 Điểm của tứ giá sẽ được gán tọa độ của texture 
            // vừa tính 
            float tex_coord[] = {
                left, bottom + texture_height,
                left, bottom,
                left + texture_width, bottom, 
                left + texture_width, bottom + texture_height
            };

            // Tạo một vertex object từ tọa độ của các điểm, 
            // tọa độ texture của các điểm và texture đã được load 
            builder_.clear();
            builder_.add_attribute("position", points, 2, 4);
            builder_.add_attribute("texCoord", tex_coord, 2, 4);
            builder_.add_texture(0, "image", texture);
            builder_.set_indices({0, 1, 2, 0, 2, 3});

            // Sinh ra vertex object 
            auto object = builder_.build();
            // Thêm nó vào sprite object 
            sprite->add_object(std::move(object));
        }
    }

    // Trả về sprite object 
    return sprite;
}

std::shared_ptr<SpriteDrawable> SpriteFactory::new_sprite(
    const std::string& filename, int rows, int cols, float height) {
    // Lấy hình ảnh và texture từ asset manager 
    auto image = asset_manager_.get_image(filename);
    auto texture = asset_manager_.get_texture(filename);

    // Tạo một sprite 
    return this->create_sprite(std::move(texture),
        image->width(), image->height(),
        rows, cols, height
    );
}


ImageDrawableFactory::ImageDrawableFactory(
        IGraphicsAssetManager& asset_manager,
        IVertexObjectBuilder& builder)
    : asset_manager_{asset_manager}, builder_{builder}
{}

IDrawablePtr ImageDrawableFactory::new_drawable(const std::string& filename, 
        float height) 
{
    // Lấy hình ảnh và texture từ asset manager 
    auto image = asset_manager_.get_image(filename);
    auto texture = asset_manager_.get_texture(filename);

    // Tính toán giá trị chiều rộng sẽ vẽ 
    // Nhờ giá trị chiều cao đã cung cấp và chiều rộng + chiều cao của 
    // ảnh 
    float width = height * image->width() / image->height();

    // Tọa độ 4 điểm của tứ giác 
    float points[] = {
        -width / 2, height / 2,
        -width / 2, -height / 2,
        width / 2, -height / 2,
        width / 2, height / 2
    };

    // Tọa độ của texture ứng với 4 điểm 
    float tex_coord[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    // Thiết lập các giá trị vào vertex object builder 
    builder_.clear();
    builder_.add_attribute("position", points, 2, 4);
    builder_.add_attribute("texCoord", tex_coord, 2, 4);
    builder_.add_texture(0, "image", texture);
    builder_.set_indices({0, 1, 2, 0, 2, 3});

    // Sinh ra một vertex object 
    auto object = builder_.build();
    // Tạo một Drawable 
    auto result = std::make_shared<Drawable>(std::move(object));
    // Trả về giá trị drawable 
    return result;
}

} // namespace tung
