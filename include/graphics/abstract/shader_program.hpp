#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "drawable.hpp"

namespace tung {

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
