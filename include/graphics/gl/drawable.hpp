#ifndef GRAPHICS_GL_DRAWABLE_H
#define GRAPHICS_GL_DRAWABLE_H

#include "../abstract/shader.hpp"
#include "../abstract/object.hpp"

namespace tung {

class Drawable: public IDrawable {
protected:
    glm::mat4 model_matrix_;
    glm::mat4 translation_matrix_;
    glm::mat4 rotation_matrix_;
    IVertexObjectPtr object_;

public:
    Drawable(IVertexObjectPtr object);

    Drawable();

    const glm::mat4& model_matrix() const override;

    void on_draw(IShaderProgram& program) override;

    void translate(glm::vec3 vec) override;

    void rotate(float angle, glm::vec3 orientation) override;
};

class DrawableGroup: public Drawable, public IDrawableManager {
protected:
    std::vector<IDrawablePtr> drawables_;

public:
    DrawableGroup();

    void on_draw(IShaderProgram& program) override;

    void attach_drawable(const IDrawablePtr& drawable) override;

    void detach_drawable(const IDrawablePtr& drawable) override;
};

} // namespace tung

#endif
