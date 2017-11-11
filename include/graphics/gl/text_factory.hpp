#ifndef TEXT_HPP
#define TEXT_HPP

#include <graphics/abstract/text.hpp>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/abstract/object.hpp>
#include <graphics/color.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>
#include <tuple>

namespace tung {

class TextFactory {
private:
    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& object_builder_;
    FT_Face face_;
    std::unordered_map<char, ITexturePtr> cache_;
    const Color color_;

    ITexturePtr get_texture(const unsigned char *buffer, 
            int width, int height);

    std::tuple<IDrawablePtr, int, int, int, int> 
        create_drawable(float ratio, const std::string& text);

public:
    TextFactory(const std::string& font, Color color,
            ITextureFactory& texture_factory,
            IVertexObjectBuilder& builder);

    ITextPtr create_for_2d(int font_size, float height, 
            const std::string& text);

    ITextPtr create_for_ui(int font_size, const std::string& text);
};

} // namespace tung

#endif
