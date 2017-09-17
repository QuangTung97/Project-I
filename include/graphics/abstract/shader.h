#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

namespace tung {

struct IShaderProgram;

struct IDrawable {
    virtual void on_draw() = 0;

    virtual void on_attach_drawable(IShaderProgram& program) = 0;

    virtual void on_detach_drawable(IShaderProgram& program) = 0;
};

struct IDrawableGroup: IDrawable {
    virtual void attach_drawable(IDrawable& drawable);

    virtual void detach_drawable(IDrawable& drawable);
};

struct IShaderProgram {
    virtual void predraw() = 0;

    virtual void draw() = 0;

    virtual void postdraw() = 0;

    virtual std::unordered_map<std::string, int> locations() = 0;

    virtual void attach_drawable(IDrawable& drawable) = 0;

    virtual void detach_drawable(IDrawable& drawable) = 0;
};

} // namespace tung

#endif
