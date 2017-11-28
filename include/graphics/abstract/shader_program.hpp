#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "drawable.hpp"

namespace tung {

// Chứa thông tin của một chương trình shader trong OpenGL 
struct IShaderProgram {
    // Tiền xử lý trước khi vẽ
    // @width: Chiều rộng màn hình 
    // @height: Chiều cao màn hình. 
    virtual void predraw(float width, float height) = 0;

    // Vẽ toàn bộ các object trong shader này. 
    virtual void draw() = 0;

    // Hậu xử lý sau khi đã vẽ.
    virtual void postdraw() = 0;

    // Return: một dictionary của tên thuộc tính và chỉ số của thuộc tính 
    // trong chương trình shader
    virtual const std::unordered_map<std::string, int>& locations() = 0;

    // @drawable: gốc drawable.
    // Thiết lập drawable gốc cho chương trình shader này. 
    virtual void set_drawable(const IDrawablePtr& drawable) = 0;

    // Return: Một std::vector các ma trận 4x4 
    // chứa thông tin phục vụ cho tính toán vị trí cho từng object. 
    virtual std::vector<glm::mat4>& model_matrix_stack() = 0;

    // Destructor
    virtual ~IShaderProgram() {}
};

} // namespace tung

#endif
