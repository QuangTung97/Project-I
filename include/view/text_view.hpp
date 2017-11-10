#ifndef VIEW_TEXT_VIEW_HPP
#define VIEW_TEXT_VIEW_HPP

#include <view/view.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/text_factory.hpp>

namespace tung {

class TextView: public View {
protected:
    static ITextFactory *text_factory_;
    IDrawablePtr text_drawable_;
    int font_size_;
    std::string text_;

public:
    TextView(float x, float y, float width, float height, 
            int font_size, const std::string& text);

    static void set_text_factory(ITextFactory& factory) {
        text_factory_ = &factory;
    }

    void set_text(const std::string& text);

    void set_font_size(int size);

    void set_size(float, float) override;

    virtual ~TextView() {}
};

} // namespace tung

#endif
