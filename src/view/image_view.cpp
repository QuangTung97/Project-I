#include <view/image_view.hpp>

namespace tung {

IVertexObjectBuilder *ImageView::builder_ = nullptr;
IGraphicsAssetManager *ImageView::asset_manager_ = nullptr;

ImageView::ImageView(float x, float y, float width, float height, 
        const std::string& filename) 
: View(x, y, width, height), filename_{filename}
{
    drawable_ = std::make_shared<Drawable>();
    drawable_->translate(glm::vec3{x, y, 0});
    validate();
}

void ImageView::validate() {
    auto& builder = *builder_;
    auto& asset_manager = *asset_manager_;

    float points[] = {
        0, 0,
        0, h_,
        w_, h_,
        w_, 0
    };

    float tex_coord[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    texture_ = asset_manager.get_texture(filename_);

    builder.clear();
    builder.add_attribute("position", points, 2, 4);
    builder.add_attribute("texCoord", tex_coord, 2, 4);
    builder.add_texture(0, "image", texture_);
    builder.set_indices({0, 1, 2, 0, 2, 3});

    auto object = builder.build();
    drawable_->set_vertex_object(std::move(object));
    drawable_->translate(glm::vec3{x_, y_, 0});
}

void ImageView::set_size(float width, float height) {
    View::set_size(width, height);
    validate();
}

void ImageView::set_image(const std::string& filename) {
    filename_ = filename;
    validate();
}

} // namespace tung
