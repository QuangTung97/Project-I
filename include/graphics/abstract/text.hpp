#ifndef GRAPHICS_ABSTRACT_TEXT_HPP
#define GRAPHICS_ABSTRACT_TEXT_HPP

#include <memory>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/color.hpp>

namespace tung {

// class chứ thông tin các lỗi khi load font, tạo text. 
class TextError: public std::exception {
private:
    std::string str_;

public:
    // constructor
    // @msg: thông tin chi tiết của lỗi. 
    TextError(std::string msg): str_{std::move(msg)} {}

    // Return: thông tin chi tiết của lỗi. 
    const char *what() const noexcept override {
        return str_.c_str();
    }
};

// Interface quản lý các dòng văn bản hiện thị lên màn hình. 
struct IText {
    // Return: Drawable của văn bản này. 
    virtual const IDrawablePtr& get_drawable() const = 0;

    // Return: Chiều rộng của dòng văn bản. 
    virtual int get_width() const = 0;

    // Return: Chiều cao của dòng văn bản. 
    virtual int get_height() const = 0;

    // Return: Vị trí bắt đầu của văn bản, từ trái sang. Quy định bởi Glyph trong FreeType. 
    virtual int get_left() const = 0;
    
    // Return: Vị trí bắt đầu của văn bản, từ trên xuống. Quy định bởi Glyph trong FreeType. 
    virtual int get_top() const = 0;

    // Destructor
    virtual ~IText() {}
};

typedef std::unique_ptr<IText> ITextPtr;

} // namespace tung

#endif
