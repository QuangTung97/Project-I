#include <graphics/gl/vertex_object.h>
#include <iostream>
#include <cassert>

namespace tung {

// Vertex Object
void VertexObject::draw() {
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices_.size(),
            GL_UNSIGNED_SHORT, indices_.data());
}

VertexObject::~VertexObject() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

// Vertex Object Builder
VertexObjectBuilder::VertexObjectBuilder(
        IShaderProgram& program)
    : locations_(program.locations())
{}

void VertexObjectBuilder::clear() {
    attributes_.clear();
    indices_.clear();
}

void VertexObjectBuilder::add_attribute(
        const std::string& name,
        const float *data, int dimension_count,
        int element_count) 
{
    this->element_count_ = element_count;

    Attribute attrib;
    attrib.name_ = name;
    attrib.data_ = data;
    attrib.dimension_count_ = dimension_count;
    attrib.element_count_ = element_count;
    attributes_.push_back(attrib);
}

void VertexObjectBuilder::set_indices(
        const std::vector<unsigned short>& indices) 
{
    this->indices_ = indices;
}

IVertexObjectPtr VertexObjectBuilder::build() {
    auto result = std::make_unique<VertexObject>();
    assert (indices_.size() != 0);
    result->indices_ = std::move(this->indices_);

    int stride = 0;
    int total_dimension = 0;
    for (auto& attrib: attributes_) {
        total_dimension += attrib.dimension_count_;
        stride += attrib.dimension_count_ * sizeof(float);
    }

    std::vector<float> data;
    data.reserve(total_dimension * element_count_);

    // Copy data
    for (int i = 0; i < element_count_; i++) {
        for (auto& attrib: attributes_) {
            for (int dimen = 0; 
                    dimen < attrib.dimension_count_; dimen++) {
                float e = attrib.data_[attrib.offset_++];
                data.push_back(e);
            }
        }
    }

    glGenBuffers(1, &result->vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, result->vbo_);
	glBufferData(GL_ARRAY_BUFFER, 
            element_count_ * stride, 
            data.data(), GL_STATIC_DRAW);


    glGenVertexArrays(1, &result->vao_);
    glBindVertexArray(result->vao_);
	glBindBuffer(GL_ARRAY_BUFFER, result->vbo_);

    for (auto& attrib: attributes_) {
        glEnableVertexAttribArray(locations_.at(attrib.name_));

        glVertexAttribPointer(locations_.at(attrib.name_), 
                attrib.dimension_count_, GL_FLOAT, 
                GL_FALSE, stride, nullptr);
    }
    return result;
}

VertexObjectBuilder::~VertexObjectBuilder() {}

} // namespace tung
