#ifndef GRAPHICS_GL_NULL_DRAWABLE_HPP
#define GRAPHICS_GL_NULL_DRAWABLE_HPP

#include <graphics/abstract/drawable.hpp>

namespace tung {

class NullDrawable: public IDrawable {
private:
    const glm::mat4 model_matrix_;

public:
    NullDrawable();

    const glm::mat4& model_matrix() const override;

    void on_draw(IShaderProgram&) override {}
    
    void set_vertex_object(IVertexObjectPtr) override {}

    void show() override {}

    void hide() override {}

    void translate(glm::vec3) override {}

    void rotate(float, glm::vec3) override {}

    virtual ~NullDrawable() {}
};

} // namespace tung

#endif
