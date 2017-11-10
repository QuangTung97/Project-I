#ifndef GRAPHICS_DRAWABLE_HPP
#define GRAPHICS_DRAWABLE_HPP

#include <graphics/abstract/drawable.hpp>
#include <graphics/abstract/object.hpp>

namespace tung {

class Drawable: public IDrawable {
protected:
    glm::mat4 model_matrix_;
    glm::mat4 translation_matrix_;
    glm::mat4 rotation_matrix_;
    IVertexObjectPtr object_;
    bool hidden_ = false;

public:
    Drawable(IVertexObjectPtr object);

    Drawable();

    const glm::mat4& model_matrix() const override;

    void on_draw(IShaderProgram& program) override;

    void set_vertex_object(IVertexObjectPtr object) override;

    void show() override { hidden_ = false; }

    void hide() override { hidden_ = true; }

    void rotate(float angle, glm::vec3 orientation) override;

    void translate(glm::vec3 vec) override;

    virtual ~Drawable();
};

class DrawableGroup: public Drawable, public IDrawableManager {
private:
    std::vector<IDrawablePtr> drawables_;

public:
    DrawableGroup();

    void on_draw(IShaderProgram& program) override;

    void attach_drawable(const IDrawablePtr& drawable) override;

    void detach_drawable(const IDrawablePtr& drawable) override;

    void clear() override;

    virtual ~DrawableGroup();
};

} // namespace tung

#endif
