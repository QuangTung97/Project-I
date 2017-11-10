#include <view/text_view.hpp>
#include <cassert>

namespace tung {

ITextFactory *TextView::text_factory_ = nullptr;

TextView::TextView(float x, float y, float width, float height, 
        int font_size, const std::string& text) 
: View(x, y, width, height),
    font_size_{font_size},
    text_{text}
{
    drawable_ = std::make_shared<DrawableGroup>();
    auto group = std::dynamic_pointer_cast<DrawableGroup>(drawable_);

    auto& factory = *text_factory_;
    text_drawable_ = factory.create(font_size, h_, text);
    group->attach_drawable(text_drawable_);
    group->translate({x, y, 0});
}

void TextView::set_text(const std::string& text) {
    text_ = text;
    auto& factory = *text_factory_;
    auto group = std::dynamic_pointer_cast<DrawableGroup>(drawable_);
    text_drawable_ = factory.create(font_size_, h_, text_);
    group->clear();
    group->attach_drawable(text_drawable_);
    group->translate({x_, y_, 0});
}

void TextView::set_font_size(int size) {
    font_size_ = size;
    auto& factory = *text_factory_;
    auto group = std::dynamic_pointer_cast<DrawableGroup>(drawable_);
    text_drawable_ = factory.create(font_size_, h_, text_);
    group->clear();
    group->attach_drawable(text_drawable_);
    group->translate({x_, y_, 0});
}

void TextView::set_size(float width, float height) {
    assert(false);
}

} // namespace tung
