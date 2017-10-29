#include <graphics/gl/image_drawable_factory.hpp>
#include <graphics/gl/sprite_factory.hpp>

namespace tung {

SpriteFactory::SpriteFactory(IImageLoader& loader, 
        ITextureFactory& texture_factory,
        IVertexObjectBuilder& builder)
    : loader_{loader}, texture_factory_{texture_factory}, builder_{builder}
{}

std::shared_ptr<SpriteDrawable> SpriteFactory::new_sprite(
    std::string image_file, int rows, int cols, float height) {
    auto sprite = std::make_shared<SpriteDrawable>();

    auto image = loader_.load(image_file);
    auto texture = texture_factory_.create(image);

    float width = height * image->width() / image->height();

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

    return sprite;
}


ImageDrawableFactory::ImageDrawableFactory(IImageLoader& loader, 
        ITextureFactory& texture_factory,
        IVertexObjectBuilder& builder)
    : loader_{loader}, texture_factory_{texture_factory}, builder_{builder}
{}

IDrawablePtr ImageDrawableFactory::new_drawable(std::string image_file, 
        float height) 
{
    auto image = loader_.load(image_file);
    auto texture = texture_factory_.create(image);

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
    return result;
}

} // namespace tung