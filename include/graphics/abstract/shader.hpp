#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace tung {

struct IShaderProgram;

struct IDrawable {
    virtual const glm::mat4& model_matrix() const = 0;

    virtual void on_draw(IShaderProgram& program) = 0;

    virtual void translate(glm::vec3 vec) = 0;

    virtual void rotate(float angle, glm::vec3 orientation) = 0;

    virtual ~IDrawable() {}
};

typedef std::shared_ptr<IDrawable> IDrawablePtr;

struct IDrawableManager {
    virtual void attach_drawable(const IDrawablePtr& drawable) = 0;

    virtual void detach_drawable(const IDrawablePtr& drawable) = 0;

    virtual ~IDrawableManager() {}
};

struct IShaderProgram {
    virtual void predraw(float width, float height) = 0;

    virtual void draw() = 0;

    virtual void postdraw() = 0;

    virtual const std::unordered_map<std::string, int>& locations() = 0;

    virtual void set_drawable(const IDrawablePtr& drawable) = 0;

    virtual std::vector<glm::mat4>& model_matrix_stack() = 0;

    virtual ~IShaderProgram() {}
};

} // namespace tung

#endif
