#ifndef VERTEX_OBJECT_H
#define VERTEX_OBJECT_H

#include <graphics/abstract/shader.h>
#include <graphics/abstract/object.h>
#include <GL/glew.h>
#include <vector>

namespace tung {

// IVertexObject::~IVertexObject() {}

// IVertexObjectBuilder::~IVertexObjectBuilder() {}

class VertexObject: public IVertexObject {
private:
    GLuint vbo_;
    GLuint vao_;
    std::vector<unsigned short> indices_;
    friend class VertexObjectBuilder;

public:
    void draw() override;

    virtual ~VertexObject();
};

class VertexObjectBuilder: public IVertexObjectBuilder {
private:
    int element_count_ = 0;
    std::unordered_map<std::string, int> locations_;
    std::vector<unsigned short> indices_;

    struct Attribute {
        std::string name_;
        const float *data_;
        int dimension_count_;
        int element_count_;
        int offset_ = 0;
    };

    std::vector<Attribute> attributes_;

public:
    VertexObjectBuilder(IShaderProgram& program);

    void clear() override;

    void add_attribute(const std::string& name,
            const float *data, int dimension_count,
            int element_count) override;

    void set_indices(
            const std::vector<unsigned short>& indices) override;

    IVertexObjectPtr build() override;

    virtual ~VertexObjectBuilder();
};

} // namespace tung

#endif
