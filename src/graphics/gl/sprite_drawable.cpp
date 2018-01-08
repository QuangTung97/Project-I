#include <graphics/gl/sprite_drawable.hpp>
#include <GL/glew.h>
#include <graphics/gl/shader_program.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tung {

SpriteDrawable::SpriteDrawable()
: Drawable() {}

void SpriteDrawable::on_draw(IShaderProgram& program) {
    // Lấy vị trí của ma trận model 
    int model_location = program.locations().at("modelMatrix");
    // Lấy giá trị của model matrix từ top của stack 
    auto& stack = program.model_matrix_stack();
    // Tính toán model matrix mới 
    glm::mat4 model = stack.back() * model_matrix_;

    // Update giá trị của model matrix mới 
    glUniformMatrix4fv(model_location, 1,
            GL_FALSE, glm::value_ptr(model));
    
    // Vẽ vertex object ứng với sprite hiện tại 
    objects_[current_sprite_]->draw();
}

void SpriteDrawable::use_sprite(int index) {
    current_sprite_ = index;
}

int SpriteDrawable::current_sprite() const {
    return current_sprite_;
}

int SpriteDrawable::get_sprite_count() const {
    // Trả về số vertex object 
    return objects_.size();
}

void SpriteDrawable::add_object(IVertexObjectPtr object) {
    // push vào phía sau của danh sách các vertex object 
    objects_.push_back(std::move(object));
}

} // namespace tung
