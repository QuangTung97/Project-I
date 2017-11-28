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

// class nhăm sinh ra các IText
class TextFactory {
private:
    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& object_builder_;
    FT_Face face_;
    std::unordered_map<char, ITexturePtr> cache_;
    const Color color_;

    // @buffer: Dữ liệu dưới dạng nhị phân 
    // (hình ảnh nhưng chỉ có một phần tử màu) 
    // của các chữ cái sau khi đã được tạo ra từ FreeType. 
    // width: chiều rộng của hình ảnh
    // height: chiều cao của hình ảnh
    ITexturePtr get_texture(const unsigned char *buffer, 
            int width, int height);

    // @ratio: Tỉ lệ giữa hình ảnh thực tế sẽ được vẽ và hình ảnh đã có. 
    // @text: Văn bản sẽ được tạo. 
    // Return: Một tuple chứa: 
    // + Con trỏ trỏ đến Drawable. 
    // + max top: giá trị lớn nhất của top trong Glyph
    // + max left: giá trị lớn nhất của left trong Glyph
    // + max width: giá trị lớn nhất của width trong Glyph
    // + max height: giá trị lớn nhất của height trong Glyph
    std::tuple<IDrawablePtr, int, int, int, int> 
        create_drawable(float ratio, const std::string& text);

public:
    // Constructor
    // @font: Đường dẫn đến font sẽ được tạo. 
    // @color: Màu của chữ. 
    // @texture_factory: Factory để tạo texture. 
    // @builder: Builder để tạo Vertex Object. 
    TextFactory(const std::string& font, Color color,
            ITextureFactory& texture_factory,
            IVertexObjectBuilder& builder);

    // @font_size: kích thước của font. 
    // @font_height: kích thước thực tế của font khi được vẽ lên màn hình. 
    // @text: Xâu văn bản. 
    // Return: Con trỏ trỏ đến IText
    ITextPtr create_for_2d(int font_size, float height, 
            const std::string& text);

    // @font_size: kích thước của font. 
    // @text: Xâu văn bản. 
    // Return: Con trỏ trỏ đến IText
    ITextPtr create_for_ui(int font_size, const std::string& text);
};

} // namespace tung

#endif
