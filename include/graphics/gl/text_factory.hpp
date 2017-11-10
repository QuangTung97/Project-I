#ifndef TEXT_HPP
#define TEXT_HPP

#include <graphics/abstract/text_factory.hpp>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/color.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>

namespace tung {

class TextFactory: public ITextFactory {
private:
    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& object_builder_;
    FT_Face face_;
    std::vector<IDrawablePtr> drawable_list_;
    std::unordered_map<char, ITexturePtr> cache_;
    const Color color_;

    ITexturePtr get_texture(const unsigned char *buffer, 
            int width, int height);

public:
    TextFactory(const std::string& font, Color color,
            ITextureFactory& texture_factory,
            IVertexObjectBuilder& builder);

    IDrawablePtr create(int font_size, float height, 
            const std::string& str) override;
};

} // namespace tung

#endif