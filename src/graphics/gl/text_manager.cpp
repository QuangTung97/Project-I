#include <graphics/gl/text_manager.hpp>

namespace tung {

TextManager::TextManager(ITextureFactory& texture_factory,
    IVertexObjectBuilder& builder)
: texture_factory_{texture_factory},
    object_builder_{builder} 
{
    set_default_font();
    set_default_font_size();
    set_default_color();
}

TextManager::Key TextManager::get_key() const {
    return std::make_tuple(font_, color_.red, color_.green, color_.blue);
}

ITextPtr TextManager::get_text(const std::string& str) {
    auto key = get_key();
    auto it = factories_.find(key);
    if (it == factories_.end()) {
        auto factory = std::make_unique<TextFactory>(
            font_, color_, texture_factory_, object_builder_);
        bool successful = false;
        std::tie(it, successful) = 
            factories_.insert(std::make_pair(key, std::move(factory)));
        if (!successful)
            throw TextError("Can't get_text");
    }
        
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