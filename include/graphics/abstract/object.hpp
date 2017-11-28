#ifndef GRAPHICS_VERTEX_OBJECT_H
#define GRAPHICS_VERTEX_OBJECT_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "texture.hpp"

namespace tung {

// Interface chứa thông tin của các VertexObject (Vertex Buffer và Vertex Arrray) trong OpenGL 
struct IVertexObject {
    // Vẽ Vertex Object này lên màn hình 
    virtual void draw() = 0;

    // Destructor 
    virtual ~IVertexObject() {}
};

typedef std::unique_ptr<IVertexObject> IVertexObjectPtr;

// Interface cho việc build vertex object 
struct IVertexObjectBuilder {
    // Xóa các dự liệu đệm từ lần build trước đó.
    virtual void clear() = 0;

    // Thêm thuộc tính vào vertex object. 
    // @name: Tên thuộc tính trong chương trình shader
    // @data: Dữ liệu của thuộc tính. 
    // @dimension_count: Số chiều của thuộc tính. Ví dụ tọa độ (x, y) sẽ là 2 chiều. 
    virtual void add_attribute(
            const std::string& name,
            const float *data, int dimension_count,
            int element_count) = 0;

    // Thêm một texture vào vertex object 
    // @active_number: Chỉ số để xác định texture 
    // @name: tên thuộc tính trong chương trình shader 
    // @texture: Shared_ptr trỏ đến texture cần được thêm. 
    virtual void add_texture(
            unsigned int active_number,
            const std::string& name,
            const ITexturePtr& texture) = 0;

    // Thiết lập mảng chỉ số để vẽ các tam giác. 
    // @indices: một std::vector các chỉ số. 
    // Ví dụ hình vuông có 4 đỉnh có chỉ số lần lượt là 0, 1, 2, 3.
    // Thì để vẽ toàn bộ hình vuông, ta cần mảng các chỉ số là: 
    // 0, 1, 2, 0, 2, 3
    virtual void set_indices(const std::vector<unsigned short>& indices) = 0;

    // build vertex object
    // Return: unique_ptr trỏ đến vertex object
    virtual IVertexObjectPtr build() = 0;

    // Destructor
    virtual ~IVertexObjectBuilder() {}
};

} // namespace tung

#endif
