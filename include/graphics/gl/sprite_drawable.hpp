#ifndef GRAPHICS_GL_SPRITE_DRAWABLE_HPP
#define GRAPHICS_GL_SPRITE_DRAWABLE_HPP

#include "drawable.hpp"
#include <vector>

namespace tung {

// Class để hiển thị hình ảnh động (ví dụ vụ nổ)
class SpriteDrawable: public Drawable {
protected:
    std::vector<IVertexObjectPtr> objects_;
    int current_sprite_ = 0;

public:
    SpriteDrawable();

    // @index: Chỉ số của frame(sprite) sẽ được vẽ. 
    void use_sprite(int index);

    // Return: Giá trị hiện thời của chỉ số frame. 
    int current_sprite() const;

    // Return: Số lượng các frame(sprite) của Drawable này. 
    int get_sprite_count() const;

    // @object: Object ứng một frame của vụ nổ. 
    void add_object(IVertexObjectPtr object);

    void on_draw(IShaderProgram& program) override;
};

} // namespace tung

#endif