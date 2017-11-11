#ifndef VIEW_TEXT_VIEW_HPP
#define VIEW_TEXT_VIEW_HPP

#include <view/view.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/text_manager.hpp>

namespace tung {

class TextView: public View {
protected:
    static ITextManager *text_manager_;
    ITextPtr text_;

    int font_size_;
    Color color_;
    std::string string_;

    void validate();

public:
    TextView(float x, float y, 
        int font_size, const std::string& text);

    TextView(float x, float y, 
        int font_size, Color color, const std::string& text);

    static void set_text_manager(ITextManager& manager) {
        text_manager_ = &manager;
    }

    void set_text(const std::string& text);

    void set_font_size(int size);

    void set_color(Color color);

    void set_size(float, float) override;

    virtual ~TextView() {}
};

} // namespace tung

#endif
