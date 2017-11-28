#ifndef GRAPHICS_ABSTRACT_DRAWABLE_HPP
#define GRAPHICS_ABSTRACT_DRAWABLE_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>

#include "object.hpp"

namespace tung {

struct IShaderProgram;

// struct IDrawable: là một interface 
// chứa thông tin để vẽ được một object nào đó lên màn hình 
struct IDrawable {
    // Lấy ma trận model để dùng cho tính toán sau này. 
    virtual const glm::mat4& model_matrix() const = 0;

    // @program: Chương trình shader
    // Hàm dùng để vẽ object Drawable này lên màn hình 
    virtual void on_draw(IShaderProgram& program) = 0;

    // @object: (là unique_ptr)
    // Thiết lập object cần được vẽ
    virtual void set_vertex_object(IVertexObjectPtr object) = 0;

    // Hiển thị 
    virtual void show() = 0;
    
    // Ẩn đi object 
    virtual void hide() = 0;

    // @vec: Tọa độ (theo x, y, z)
    // Di chuyển object đến tọa độ xác định bởi vec 
    virtual void translate(glm::vec3 vec) = 0;

    // @angle: Góc cần xoay.
    // @orientation: Hướng xoay. 
    // Xoay vật theo một góc angle, xung quay một trục xác định bởi orientation
    virtual void rotate(float angle, glm::vec3 orientation) = 0;

    // @Destructor
    virtual ~IDrawable() {}
};

typedef std::shared_ptr<IDrawable> IDrawablePtr;

// IDrawableManager: là interface nhằm mục đích cho các Drawable thành một tổ chức cây. 
// Mỗi một IDrawableManager là một node của cây. 
// Mỗi một IDrawable là một lá 
struct IDrawableManager {
    // @drawable: node cần được thêm vào cây tại node hiện tại 
    virtual void attach_drawable(const IDrawablePtr& drawable) = 0;

    // @drawable: node cần được xóa tại node hiện tại 
    virtual void detach_drawable(const IDrawablePtr& drawable) = 0;

    // Xóa toàn bộ các node con của cây. 
    virtual void clear() = 0;

    // Destructor 
    virtual ~IDrawableManager() {}
};

typedef std::shared_ptr<IDrawableManager> IDrawableManagerPtr;

} // namespace tung

#endif
