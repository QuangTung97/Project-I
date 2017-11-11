#ifndef GRAPHICS_ABSTRACT_TEXT_MANAGER_HPP
#define GRAPHICS_ABSTRACT_TEXT_MANAGER_HPP

#include "text.hpp"

namespace tung {

struct ITextManager {
    virtual void set_font(const std::string& font) = 0;

    virtual void set_default_font() = 0;

    virtual void set_font_size(int font_size) = 0;

    virtual void set_default_font_size() = 0;

    virtual void set_color(Color color) = 0;

    virtual void set_default_color() = 0;

    virtual ITextPtr get_text(const std::string& text) = 0;

    virtual ~ITextManager() {}
};

} // namespace tung

#endif
