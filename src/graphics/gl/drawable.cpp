#include <GL/glew.h>
#include <graphics/gl/drawable.hpp>
#include <graphics/gl/shader_program.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace tung {

// Drawable Constructor 
// Khởi tạo các ma trận: model, translation, rotation 
// Khởi tạo vertext object 
Drawable::Drawable(IVertexObjectPtr object)
    : model_matrix_(1.0), 
    translation_matrix_(1.0),
    rotation_matrix_(1.0),
    object_{std::move(object)} 
{}

// Drawable Constructor 
// Khởi tạo các ma trận: model, translation, rotation 
Drawable::Drawable()
    : model_matrix_(1.0), 
    translation_matrix_(1.0),
    rotation_matrix_(1.0)
{}

const glm::mat4& Drawable::model_matrix() const {
    return model_matrix_;
}

void Drawable::on_draw(IShaderProgram& program) {
    // Nếu object_ không có thì trả về 
    if (object_ == nullptr)
        return;
    //  Nếu đang ở chế độ ẩn thì trả về 
    if (hidden_)
        return;

    // Lấy vị trí của ma trận model trong vertex shader 
    int model_location = program.locations().at("modelMatrix");
    // Lấy model matrix stack của chương trình 
    auto& stack = program.model_matrix_stack();
    // Tính giá trị của model matrix mới 
    glm::mat4 model = stack.back() * model_matrix_;

    // Update giá trị của model matrix mới lên trên Rendering Pipeline
    glUniformMatrix4fv(model_location, 1,
            GL_FALSE, glm::value_ptr(model));
    // Vẽ vertex object 
    object_->draw();
}

void Drawable::set_vertex_object(IVertexObjectPtr object) {
    object_ = std::move(object);
}

void Drawable::rotate(float angle, glm::vec3 orientation) {
    // Tạo một ma trận quay bằng 
    // một góc và một hướng 
    rotation_matrix_ 
        = glm::rotate(glm::mat4(1.0), angle, orientation);
    // Update lại giá trị của model matrix 
    model_matrix_ = translation_matrix_ * rotation_matrix_;
}

void Drawable::translate(glm::vec3 vec) {
    // Tạo một  ma trận chuyển vị nhờ vector chuyển vị 
    translation_matrix_ 
        = glm::translate(glm::mat4(1.0), vec);
    // Update lại giá trị của model matrix 
    model_matrix_ = translation_matrix_ * rotation_matrix_;
}

Drawable::~Drawable() {
}

// DrawableGroup
DrawableGroup::DrawableGroup(): Drawable() {}

void DrawableGroup::on_draw(IShaderProgram& program) {
    // Gọi on_draw của super class 
    Drawable::on_draw(program);

    // Lấy model matrix stack của ShaderProgram 
    auto& stack = program.model_matrix_stack();
    // Tính toán giá trị model matrix mới push nó vào stack 
    stack.push_back(stack.back() * model_matrix_);

    // Vẽ từng drawable 
    for (auto& drawable: drawables_) {
        drawable->on_draw(program);
    }
    // Pop giá trị của model matrix mới 
    stack.pop_back();
}

void DrawableGroup::attach_drawable(const IDrawablePtr& drawable)
{
    // Tìm iterator của drawable trong drawables_ 
    auto find_it = std::find(drawables_.begin(), drawables_.end(), drawable);
    if (find_it == drawables_.end()) {
        // Nếu không tìm thấy, push nó vào trong danh sách 
        drawables_.push_back(drawable);
    }
}

void DrawableGroup::detach_drawable(const IDrawablePtr& drawable)
{
    // Xóa các drawable trong danh sách drawables_
    drawables_.erase(
            std::remove(drawables_.begin(), 
                drawables_.end(), drawable),
            drawables_.end()
    );
}

void DrawableGroup::clear() {
    // Xóa toàn bộ các drawable trong danh sách drawables_
    drawables_.clear();
}

DrawableGroup::~DrawableGroup() {
}

} // namespace tung
