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

    int get_width() const override {
        return width_;
    }

    int get_height() const override {
        return height_;
    }

    int get_top() const override {
        return top_;
    }

    int get_left() const override {
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
    // Nếu freetype chưa được khởi tạo 
    if (!freetype_is_initialized) {
        freetype_is_initialized = true;
        // Khởi tạo freetype 
        auto result = FT_Init_FreeType(&freetype);
        // Throw nếu không được 
        if (result)
            throw TextError("Can't init freetype");
    }

    // Tạo một face (ứng với một font) 
    auto result 
        = FT_New_Face(freetype, font.c_str(), 0, &face_);
    // Throw nếu không được 
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
    // Tạo một drawable group để lưu trữ các kí tự 
    auto group = std::make_shared<DrawableGroup>();

    // Duyệt qua từng kí tự 
    for (auto ch: text) {
        // tính toán các pixel của kí tự đấy 
        auto result = FT_Load_Char(face_, ch, FT_LOAD_RENDER);
        // throw nếu không được 
        if (result)
            throw TextError("Can't load character");

        // Nhận data struct ứng với kí tự 
        FT_GlyphSlot g = face_->glyph;

        // Gán giá trị thông số của glyph 
        float width = g->bitmap.width;
        float height = g->bitmap.rows;
        float top = g->bitmap_top;
        float left = g->bitmap_left;

        // Nếu không phải lần đầu tiên travel 
        if (!first_travelled) {
            first_travelled = true;
            // left nhỏ nhất bằng giá trị left của kí tự đầu tiên 
            max_left = left;
        }

        // Tính toán max top
        if (max_top < (int)top) {
            max_top = top;
        }

        // Tính toán max height 
        if (max_height < (int)height) {
            max_height = height;
        }

        last_width = width;

        // Tọa độ 4 điểm sẽ vẽ kí tự 
        float positions[] = {
            -left, -top,
            -left, height - top, 
            -left + width, height - top,
            -left + width, -top
        };

        // Scale các tọa độ theo một tỉ lệ 
        for (int i = 0; i < 8; i++)
            positions[i] *= ratio;

        // Tọa độ của texture 
        float tex_coords[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
        };

        // Sinh ra một vertex object 
        object_builder_.clear();
        object_builder_.add_attribute("position", 
                positions, 2, 4);
        object_builder_.add_attribute("texCoord",
                tex_coords, 2, 4);

        // Tìm xem trong cache đã có chứa texture của kí tự này chưa 
        auto texture_it = cache_.find(ch);
        ITexturePtr texture;
        if (texture_it != cache_.end()) {
            // Nếu đã có 
            texture = texture_it->second;
        }
        else {
            // Nếu chưa có thì sinh texture từ dữ liệu từng 
            // pixel đã tính toán trước đó 
            texture = this->get_texture(
                    g->bitmap.buffer, g->bitmap.width, g->bitmap.rows);
            cache_[ch] = texture;
        }

        object_builder_.add_texture(0, "image", texture);
        object_builder_.set_indices({0, 1, 2, 0, 2, 3});
        auto object = object_builder_.build();

        // Tạo một drawable từ vertex object 
        IDrawablePtr drawable = std::make_shared<Drawable>(
                std::move(object));
        // Dịch chuyển nó đi một khoảng 
        drawable->translate(glm::vec3{advance_x, advance_y, 0});
        group->attach_drawable(std::move(drawable));

        prev_last_advance_x = advance_x;
        advance_x += g->advance.x / 64 * ratio;
        advance_y += g->advance.y / 64 * ratio;
    }

    max_width = prev_last_advance_x + last_width;
    // Trả về các kết quả 
    return std::make_tuple(std::move(group), max_top, max_left, max_width, max_height);
}

ITextPtr TextFactory::create_for_ui(int font_size, const std::string& text) 
{
    // Tạo một face ứng với kích thước font 
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    // gọi hàm create_drawable và lấy giá trị trả về 
    IDrawablePtr drawable;
    int top, left, width, height;
    std::tie(drawable, top, left, width, height) 
        = create_drawable(1, text);

    // Tạo một text object từ drawable 
    auto result = std::make_unique<Text>(
        std::move(drawable), top, left, width, height);
    return result;
}

ITextPtr TextFactory::create_for_2d(int font_size, float font_height,
        const std::string& text) {
    // Tạo một face ứng với kích thước font 
    FT_Set_Pixel_Sizes(face_, 0, font_size);

    float ratio = font_height / font_size;

    // gọi hàm create_drawable và lấy giá trị trả về 
    IDrawablePtr drawable;
    int top, left, width, height;
    std::tie(drawable, top, left, width, height) 
        = create_drawable(ratio, text);

    // Tạo một text object từ drawable 
    auto result = std::make_unique<Text>(
        std::move(drawable), top, left, width, height);
    return std::move(result);
}

ITexturePtr TextFactory::get_texture(
        const unsigned char *buffer, 
        int width, int height) 
{
    std::vector<unsigned char> data;
    // Mở rộng kích thước vùng nhớ cho vector 
    data.reserve(width * height * 4);
    int buffer_size = width * height;

    // Duyệt qua từng byte trong buffer 
    for (int i = 0; i < buffer_size; i++) {
        // Thêm từng màu
        data.push_back(color_.red);
        data.push_back(color_.green);
        data.push_back(color_.blue);
        data.push_back(buffer[i]);
    }
    // Sinh ảnh từ dữ liệu đó 
    auto image =  std::make_shared<FontImage>(width, height, std::move(data));
    // Trả về texture sau khi sinh ảnh 
    return texture_factory_.create(image);
}

} // namespace tung
