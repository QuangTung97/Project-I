#include <view/text.hpp>
#include <graphics/gl/drawable.hpp>

namespace tung {

static FT_Library freetype;
static bool freetype_is_initialized = false;

// Text
Text::Text() {
}

const IDrawablePtr& Text::get_drawable() const {
    return vertex_object_;
}

// Text Factory
TextFactory::TextFactory(const std::string& font,
        IVertexObjectBuilder& builder)
    : object_builder_{builder} 
{
    if (!freetype_is_initialized) {
        freetype_is_initialized = true;
        auto result = FT_Init_FreeType(&freetype);
        if (result)
            throw TextError("Can't init freetype");
    }

    auto result 
        = FT_New_Face(freetype, font.c_str(), 0, &face_);
    if (result) {
        throw TextError("Can't init face");
    }
}

ITextPtr TextFactory::create(int font_size, float font_height,
        const std::string& str) {
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    drawable_list_.clear();
    float advance_x = 0;
    float advance_y = 0;

    auto group = std::make_shared<DrawableGroup>();
    auto text = std::make_unique<Text>();
    text->vertex_object_ = group;

    for (auto ch: str) {
        auto result = FT_Load_Char(face_, ch, FT_LOAD_RENDER);
        if (result)
            throw TextError("Can't load character");

        FT_GlyphSlot g = face_->glyph;
        
        float width = g->bitmap.width;
        float height = g->bitmap.rows;
        float top = g->bitmap_top;
        float left = g->bitmap_left;

        float ratio = font_height / font_size;

        float positions[] = {
            -left, top, 
            -left, top - height, 
            -left + width, top - height,
            -left + width, top
        };

        for (int i = 0; i < 8; i++)
            positions[i] *= ratio;

        float tex_coords[] = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };

        object_builder_.clear();
        object_builder_.add_attribute("position", 
                positions, 2, 4);
        object_builder_.add_attribute("texCoord",
                tex_coords, 2, 4);

        auto texture = get_texture(
                g->bitmap.buffer,
                g->bitmap.width,
                g->bitmap.rows);

        object_builder_.add_texture(0, "image", texture);
        
        auto object = object_builder_.build();
        IDrawablePtr drawable = std::make_shared<Drawable>(
                std::move(object));
        drawable->translate(glm::vec3(advance_x, advance_y, 0));
        advance_x += g->advance.x * ratio;
        advance_y += g->advance.y * ratio;

        group->attach_drawable(drawable);
    }
    return text;
}

ITexturePtr TextFactory::get_texture(
        const unsigned char *buffer, 
        int width, int height) 
{
    // TODO
}

} // namespace tung
