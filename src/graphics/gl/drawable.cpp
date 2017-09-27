#include <GL/glew.h>
#include <graphics/gl/drawable.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace tung {

// Drawable
Drawable::Drawable(IVertexObjectPtr object)
    : model_matrix_(1.0), 
    translation_matrix_(1.0),
    rotation_matrix_(1.0),
    object_{std::move(object)} 
{}

Drawable::Drawable()
    : model_matrix_(1.0), 
    translation_matrix_(1.0),
    rotation_matrix_(1.0)
{}

const glm::mat4& Drawable::model_matrix() const {
    return model_matrix_;
}

void Drawable::on_draw(IShaderProgram& program) {
    if (object_ == nullptr)
        return;

    int model_location = program.locations().at("modelMatrix");
    auto& stack = program.model_matrix_stack();
    glm::mat4 model = stack.back() * model_matrix_;

    glUniformMatrix4fv(model_location, 1,
            GL_FALSE, glm::value_ptr(model));
    object_->draw();
}

void Drawable::rotate(float angle, glm::vec3 orientation) {
    rotation_matrix_ 
        = glm::rotate(glm::mat4(1.0), angle, orientation);
    model_matrix_ = translation_matrix_ * rotation_matrix_;
}

void Drawable::translate(glm::vec3 vec) {
    translation_matrix_ 
        = glm::translate(glm::mat4(1.0), vec);
    model_matrix_ = translation_matrix_ * rotation_matrix_;
}

// DrawableGroup
DrawableGroup::DrawableGroup(): Drawable() {}

void DrawableGroup::on_draw(IShaderProgram& program) {
    Drawable::on_draw(program);

    auto& stack = program.model_matrix_stack();
    stack.push_back(stack.back() * model_matrix_);

    for (auto& drawable: drawables_) {
        drawable->on_draw(program);
    }
    stack.pop_back();
}

void DrawableGroup::attach_drawable(const IDrawablePtr& drawable)
{
    drawables_.push_back(drawable);
}

void DrawableGroup::detach_drawable(const IDrawablePtr& drawable)
{
    drawables_.erase(
            std::remove(drawables_.begin(), 
                drawables_.end(), drawable),
            drawables_.end()
    );
}

} // namespace tung
