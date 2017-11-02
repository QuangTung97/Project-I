#ifndef VIEW_IMAGE_VIEW_HPP
#define VIEW_IMAGE_VIEW_HPP

#include <view/view.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/graphics_asset_manager.hpp>

namespace tung {

class ImageView: public View {
protected:
    static IVertexObjectBuilder *builder_;
    static IGraphicsAssetManager *asset_manager_;
    ITexturePtr texture_;

public:
    ImageView(float x, float y, float width, float height, 
            const std::string& image_file);

    static void set_vertex_object_builder(IVertexObjectBuilder& builder) {
        builder_ = &builder;
    }

    static void set_asset_manager(IGraphicsAssetManager& manager) {
        asset_manager_ = &manager;
    }

    void set_size(float, float) override;

    virtual ~ImageView() {}
};

} // namespace tung

#endif
