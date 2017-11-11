#include <view/text_view.hpp>
#include <cassert>

namespace tung {

ITextManager *TextView::text_manager_ = nullptr;

TextView::TextView(float x, float y,
        int font_size, const std::string& str) 
: TextView(x, y, font_size, Color{0, 0, 0}, str)
{}

TextView::TextView(float x, float y,
        int font_size, Color color, const std::string& str) 
: View(x, y, 1, 1),
    font_size_{font_size},
    color_{color},
    string_{str}
{
    auto group = std::make_shared<DrawableGroup>();
    drawable_ = group;

    auto& manager = *text_manager_;
    manager.set_default_font();
    manager.set_font_size(font_size_);
    manager.set_color(color_);
    text_ = manager.get_text(string_);
    group->attach_drawable(text_->get_drawable());
    group->translate(glm::vec3{x, y, 0});
}

void TextView::validate() {
    auto& manager = *text_manager_;
    manager.set_default_font();
    manager.set_font_size(font_size_);
    manager.set_color(color_);
    text_ = manager.get_text(string_);

    auto group = std::dynamic_pointer_cast<DrawableGroup>(drawable_);
    group->clear();
    group->attach_drawable(text_->get_drawable());
    group->translate(glm::vec3{x_, y_, 0});
}

void TextView::set_text(const std::string& string) {
    string_ = string;
    validate();
}

void TextView::set_color(Color color) {
    color_ = color;
    validate();
}

void TextView::set_font_size(int size) {
    font_size_ = size;
    validate();
}

void TextView::set_size(float width, float height) {
    View::set_size(width, height);
}

} // namespace tung
