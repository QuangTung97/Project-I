#ifndef GRAPHICS_GL_SPRITE_DRAWABLE_HPP
#define GRAPHICS_GL_SPRITE_DRAWABLE_HPP

#include "drawable.hpp"
#include <vector>

namespace tung {

class SpriteDrawable: public Drawable {
protected:
    std::vector<IVertexObjectPtr> objects_;
    int current_sprite_ = 0;

public:
    SpriteDrawable();

    void use_sprite(int index);

    int current_sprite() const;

    int get_sprite_count() const;

    void add_object(IVertexObjectPtr object);

    void on_draw(IShaderProgram& program) override;
};

} // namespace tung

#endif