#ifndef TEXT_ABSTRACT_HPP
#define TEXT_ABSTRACT_HPP

#include <memory>
#include <graphics/abstract/shader.hpp>

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
};

typedef std::unique_ptr<IText> ITextPtr;

struct ITextFactory {
    virtual ITextPtr create(int font_size, float height, const std::string& str) = 0;
};

} // namespace tung

#endif
