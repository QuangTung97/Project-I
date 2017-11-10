#ifndef GRAPHICS_ABSTRACT_TEXT_FACTORY_HPP
#define GRAPHICS_ABSTRACT_TEXT_FACTORY_HPP

#include <memory>
#include <graphics/abstract/shader_program.hpp>

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

struct ITextFactory {
    virtual IDrawablePtr create(int font_size, float height, const std::string& str) = 0;
};

} // namespace tung

#endif
