#ifndef TEXT_HPP
#define TEXT_HPP

#include <view/abstract/text.hpp>
#include <graphics/abstract/shader.hpp>
#include <graphics/abstract/object.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace tung {

class Text: public IText {
private:
    IDrawablePtr vertex_object_;
    friend class TextFactory;

public:
    Text();

    const IDrawablePtr& get_drawable() const override;
};

class TextFactory: public ITextFactory {
private:
    IVertexObjectBuilder& object_builder_;
    FT_Face face_;
    std::vector<IDrawablePtr> drawable_list_;

    ITexturePtr get_texture(const unsigned char *buffer, 
            int width, int height);

public:
    TextFactory(const std::string& font, 
            IVertexObjectBuilder& builder);

    ITextPtr create(int font_size, float height, 
            const std::string& str) override;
};

} // namespace tung

#endif
