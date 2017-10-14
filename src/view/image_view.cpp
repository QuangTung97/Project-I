#include <view/image_view.hpp>

namespace tung {

IVertexObjectBuilder *ImageView::builder_ = nullptr;
ITextureFactory *ImageView::texture_factory_ = nullptr;

ImageView::ImageView(float x, float y, float width, float height, 
        const IImagePtr& image) 
    : View(x, y, width, height)
{
    IVertexObjectBuilder& builder = *builder_;
    ITextureFactory& texture_factory = *texture_factory_;

    float points[] = {
        0, 0,
        0, height,
        width, height,
        width, 0
    };

    float tex_coord[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    texture_ = texture_factory.create(image);

    builder.clear();
    builder.add_attribute("position", points, 2, 4);
    builder.add_attribute("texCoord", tex_coord, 2, 4);
    builder.add_texture(0, "image", texture_);
    builder.set_indices({0, 1, 2, 0, 2, 3});

    auto object = builder.build();
    drawable_ = std::make_shared<Drawable>(std::move(object));
    drawable_->translate({x, y, 0});
}

void ImageView::set_size(float width, float height) {
    View::set_size(width, height);
    IVertexObjectBuilder& builder = *builder_;

    float points[] = {
        0, 0,
        0, height,
        width, height,
        width, 0
    };

    float tex_coord[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    builder.clear();
    builder.add_attribute("position", points, 2, 4);
    builder.add_attribute("texCoord", tex_coord, 2, 4);
    builder.add_texture(0, "image", texture_);
    builder.set_indices({0, 1, 2, 0, 2, 3});

    auto object = builder.build();
    drawable_->set_vertex_object(std::move(object));
}

} // namespace tung
