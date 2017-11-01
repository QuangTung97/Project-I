#include <graphics/gl/image_drawable_factory.hpp>
#include <graphics/gl/sprite_factory.hpp>

namespace tung {

SpriteFactory::SpriteFactory(IGraphicsAssetManager& asset_manager,
        IVertexObjectBuilder& builder)
    : asset_manager_{asset_manager}, builder_{builder}
{}

std::shared_ptr<SpriteDrawable> SpriteFactory::create_sprite(
    ITexturePtr texture, int image_width, int image_height, 
    int rows, int cols, float height) 
{
    auto sprite = std::make_shared<SpriteDrawable>();

    float width = height * image_width / (float)image_height * rows / (float)cols;

    float points[] = {
        -width / 2, height / 2,
        -width / 2, -height / 2,
        width / 2, -height / 2,
        width / 2, height / 2
    };

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            float texture_width = 1.0f / cols;
            float texture_height = 1.0f / rows;
            float x = (float)col / cols;
            float y = (float)row / rows;

            float bottom = 1.0f - y - texture_height;
            float left = x;

            float tex_coord[] = {
                left, bottom + texture_height,
                left, bottom,
                left + texture_width, bottom, 
                left + texture_width, bottom + texture_height
            };

            builder_.clear();
            builder_.add_attribute("position", points, 2, 4);
            builder_.add_attribute("texCoord", tex_coord, 2, 4);
            builder_.add_texture(0, "image", texture);
            builder_.set_indices({0, 1, 2, 0, 2, 3});

            auto object = builder_.build();
            sprite->add_object(std::move(object));
        }
    }

    return std::move(sprite);
}

std::shared_ptr<SpriteDrawable> SpriteFactory::new_sprite(
    const std::string& filename, int rows, int cols, float height) {
    auto image = asset_manager_.get_image(filename);
    auto texture = asset_manager_.get_texture(filename);

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
    auto image = asset_manager_.get_image(filename);
    auto texture = asset_manager_.get_texture(filename);

    float width = height * image->width() / image->height();

    float points[] = {
        -width / 2, height / 2,
        -width / 2, -height / 2,
        width / 2, -height / 2,
        width / 2, height / 2
    };

    float tex_coord[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    builder_.clear();
    builder_.add_attribute("position", points, 2, 4);
    builder_.add_attribute("texCoord", tex_coord, 2, 4);
    builder_.add_texture(0, "image", texture);
    builder_.set_indices({0, 1, 2, 0, 2, 3});

    auto object = builder_.build();
    auto result = std::make_shared<Drawable>(std::move(object));
    return std::move(result);
}

} // namespace tung