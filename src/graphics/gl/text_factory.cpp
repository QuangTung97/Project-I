#include <graphics/gl/text_factory.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/image/font.hpp>
#include <vector>

#include <iostream>

namespace tung {

static FT_Library freetype;
static bool freetype_is_initialized = false;

// Text
class Text: public IText {
private:
    int top_, left_;
    int width_, height_;
    IDrawablePtr drawable_;

public:
    Text(IDrawablePtr drawable, int top, 
        int left, int width, int height)
    : drawable_{drawable}, 
        top_{top}, left_{left},
        width_{width}, height_{height} {}

    const IDrawablePtr& get_drawable() const override {
        return drawable_;
    }

    const int get_width() const override {
        return width_;
    }

    const int get_height() const override {
        return height_;
    }

    const int get_top() const override {
        return top_;
    }

    const int get_left() const override {
        return left_;
    }

    virtual ~Text() {}
};

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

std::tuple<IDrawablePtr, int, int, int, int> TextFactory::create_drawable(
    float ratio, const std::string& text) 
{
    bool first_travelled = false;
    int max_top = 0, max_left = 0, max_height = 0, max_width = 0;
    int last_width = 0;
    int prev_last_advance_x = 0;

    float advance_x = 0;
    float advance_y = 0;
    auto group = std::make_shared<DrawableGroup>();

    for (auto ch: text) {
        auto result = FT_Load_Char(face_, ch, FT_LOAD_RENDER);
        if (result)
            throw TextError("Can't load character");

        FT_GlyphSlot g = face_->glyph;

        float width = g->bitmap.width;
        float height = g->bitmap.rows;
        float top = g->bitmap_top;
        float left = g->bitmap_left;

        if (!first_travelled) {
            first_travelled = true;
            max_left = left;
        }

        if (max_top < (int)top) {
            max_top = top;
        }

        if (max_height < (int)height) {
            max_height = height;
        }

        last_width = width;

        float positions[] = {
            -left, -top,
            -left, height - top, 
            -left + width, height - top,
            -left + width, -top
        };

        for (int i = 0; i < 8; i++)
            positions[i] *= ratio;

        float tex_coords[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
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
        drawable->translate(glm::vec3{advance_x, advance_y, 0});
        group->attach_drawable(std::move(drawable));

        prev_last_advance_x = advance_x;
        advance_x += g->advance.x / 64 * ratio;
        advance_y += g->advance.y / 64 * ratio;
    }

    max_width = prev_last_advance_x + last_width;
    return std::make_tuple(std::move(group), max_top, max_left, max_width, max_height);
}

ITextPtr TextFactory::create_for_ui(int font_size, const std::string& text) 
{
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    IDrawablePtr drawable;
    int top, left, width, height;
    std::tie(drawable, top, left, width, height) 
        = create_drawable(1, text);

    auto result = std::make_unique<Text>(
        std::move(drawable), top, left, width, height);
    return std::move(result);
}

ITextPtr TextFactory::create_for_2d(int font_size, float font_height,
        const std::string& text) {
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    float ratio = font_height / font_size;

    IDrawablePtr drawable;
    int top, left, width, height;
    std::tie(drawable, top, left, width, height) 
        = create_drawable(ratio, text);

    auto result = std::make_unique<Text>(
        std::move(drawable), top, left, width, height);
    return std::move(result);
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
