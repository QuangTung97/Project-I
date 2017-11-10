#include <graphics/gl/text_factory.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/image/font.hpp>
#include <vector>

#include <iostream>

namespace tung {

static FT_Library freetype;
static bool freetype_is_initialized = false;

// Text Factory
TextFactory::TextFactory(
    const std::string& font, Color color,
    ITextureFactory& texture_factory,
    IVertexObjectBuilder& builder)
: color_{color},
    texture_factory_{texture_factory},
    object_builder_{builder} 
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

IDrawablePtr TextFactory::create(int font_size, float font_height,
        const std::string& str) {
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    drawable_list_.clear();
    float advance_x = 0;
    float advance_y = 0;

    auto group = std::make_shared<DrawableGroup>();

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

        auto texture_it = cache_.find(ch);
        ITexturePtr texture;
        if (texture_it != cache_.end()) {
            texture = texture_it->second;
        }
        else {
            texture = this->get_texture(
                    g->bitmap.buffer, g->bitmap.width, g->bitmap.rows);
            cache_[ch] = texture;
        }

        object_builder_.add_texture(0, "image", texture);
        object_builder_.set_indices({0, 1, 2, 0, 2, 3});
        auto object = object_builder_.build();

        IDrawablePtr drawable = std::make_shared<Drawable>(
                std::move(object));
        drawable->translate({advance_x, advance_y, 0});
        group->attach_drawable(std::move(drawable));

        advance_x += g->advance.x / 64 * ratio;
        advance_y += g->advance.y / 64 * ratio;
    }
    return std::move(group);
}

ITexturePtr TextFactory::get_texture(
        const unsigned char *buffer, 
        int width, int height) 
{
    std::vector<unsigned char> data;
    data.reserve(width * height * 4);
    int buffer_size = width * height;
    for (int i = 0; i < buffer_size; i++) {
        data.push_back(color_.red);
        data.push_back(color_.green);
        data.push_back(color_.blue);
        data.push_back(buffer[i]);
    }
    auto image =  std::make_shared<FontImage>(width, height, std::move(data));
    return texture_factory_.create(image);
}

} // namespace tung
