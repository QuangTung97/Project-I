#ifndef LOGIC_ACTOR_GRAPHICS_IMAGE_HPP
#define LOGIC_ACTOR_GRAPHICS_IMAGE_HPP

#include "component.hpp"
#include <graphics/abstract/drawable.hpp>
#include <graphics/gl/image_drawable_factory.hpp>

namespace tung {
namespace actor {

// Component phục vụ việc hiển thị hình ảnh lên màn hình 
class GraphicsImage: public Component {
private:
    IDrawablePtr drawable_;
    IDrawableManagerPtr root_;

public:
    static const ComponentId COMPONENT_ID;

    // Constructor
    // @x, @y: Tọa độ tâm của hình ảnh. 
    // @factory: factory cần thiết để tạo drawable 
    // @root: Gốc của cây drawable. 
    // @height: Chiều cao của ảnh sẽ hiển thị 
    // @filename: Đường dẫn đến thư mục hình ảnh. 
    GraphicsImage(float x, float y, 
        ImageDrawableFactory& factory, 
        IDrawableManagerPtr root,
        float height, const std::string& filename);

    ComponentId get_id() const override {
        return COMPONENT_ID;
    }

    // Cho phép hiển thị 
    void show();

    // Ẩn hình ảnh 
    void hide();

    // Di chuyển đến vị trí khác 
    void move_to(float x, float y);

    // Quay hình ảnh đi một góc ngược chiều kim đồng hồ, theo độ
    void rotate(float degree);

    ~GraphicsImage();
};

} // namespace actor
} // namespace tung

#endif