#ifndef VIEW_IMAGE_VIEW_HPP
#define VIEW_IMAGE_VIEW_HPP

#include <view/view.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/texture.hpp>

namespace tung {

class ImageView: public View {
protected:
    static IVertexObjectBuilder *builder_;
    static ITextureFactory *texture_factory_;
    ITexturePtr texture_;

public:
    ImageView(float x, float y, float width, float height, 
            const IImagePtr& image);

    static void set_vertex_object_builder(IVertexObjectBuilder& builder) {
        builder_ = &builder;
    }

    static void set_texture_factory(ITextureFactory& texture_factory) {
        texture_factory_ = &texture_factory;
    }

    void set_size(float, float) override;

    virtual ~ImageView() {}

};

} // namespace tung

#endif
