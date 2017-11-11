#ifndef GRAPHICS_ABSTRACT_TEXT_HPP
#define GRAPHICS_ABSTRACT_TEXT_HPP

#include <memory>
#include <graphics/abstract/shader_program.hpp>
#include <graphics/color.hpp>

namespace tung {

class TextError: public std::exception {
private:
    std::string str_;

public:
    TextError(std::string msg): str_{std::move(msg)} {}

    const char *what() const noexcept override {
        return str_.c_str();
    }
};

struct IText {
    virtual const IDrawablePtr& get_drawable() const = 0;

    virtual const int get_width() const = 0;

    virtual const int get_height() const = 0;

    virtual const int get_left() const = 0;
    
    virtual const int get_top() const = 0;

    virtual ~IText() {}
};

typedef std::unique_ptr<IText> ITextPtr;

} // namespace tung

#endif
