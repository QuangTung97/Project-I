#ifndef GRAPHICS_ABSTRACT_TEXT_MANAGER_HPP
#define GRAPHICS_ABSTRACT_TEXT_MANAGER_HPP

#include "text.hpp"

namespace tung {

// Interface quản lý hiển thị text lên màn hình. 
struct ITextManager {
    // @font: Đường dẫn đến file chứa font. 
    // Thiết lập font của text
    virtual void set_font(const std::string& font) = 0;

    // Thiết lập font mặc định cho manager này. 
    virtual void set_default_font() = 0;

    // @font_size: Kích thước font. 
    // Thiết lập kích thước font. 
    virtual void set_font_size(int font_size) = 0;

    // Thiết lập kích thước font mặc định. 
    virtual void set_default_font_size() = 0;

    // Thiết lập màu của chữ. 
    virtual void set_color(Color color) = 0;

    // Thiết lập màu mặc định. 
    virtual void set_default_color() = 0;

    // @text: Dòng văn bản cần được tạo. 
    // Return: Trả về một unique_ptr trỏ đến IText. 
    virtual ITextPtr get_text(const std::string& text) = 0;

    // Destructor
    virtual ~ITextManager() {}
};

} // namespace tung

#endif
