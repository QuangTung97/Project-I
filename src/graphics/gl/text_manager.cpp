#include <graphics/gl/text_manager.hpp>

namespace tung {

TextManager::TextManager(ITextureFactory& texture_factory,
    IVertexObjectBuilder& builder)
: texture_factory_{texture_factory},
    object_builder_{builder} 
{
    // Thiết lập các màu, font và kích thước font mặc định 
    set_default_font();
    set_default_font_size();
    set_default_color();
}

TextManager::Key TextManager::get_key() const {
    // Tạo một tuple từ font và các màu 
    return std::make_tuple(font_, color_.red, color_.green, color_.blue);
}

ITextPtr TextManager::get_text(const std::string& str) {
    // Lấy khóa
    auto key = get_key();
    // Tìm iterator từ khóa 
    auto it = factories_.find(key);
    if (it == factories_.end()) {
        // Nếu khóa chưa tồn tại 
        // Thì tạo một factory 
        auto factory = std::make_unique<TextFactory>(
            font_, color_, texture_factory_, object_builder_);
        bool successful = false;
        // Thêm nó vào danh sách các factory 
        std::tie(it, successful) = 
            factories_.insert(std::make_pair(key, std::move(factory)));
        // throw nếu có trùng lặp 
        if (!successful)
            throw TextError("Can't get_text");
    }
        
    // Trả về một text 
    return it->second->create_for_ui(size_, str);
}

void TextManager::set_default_font() {
    font_ = "assets/Arial.ttf";
}

void TextManager::set_default_font_size() {
    size_ = 48;
}

void TextManager::set_default_color() {
    color_ = Color{0, 0, 0};
}

} // namespace tung
