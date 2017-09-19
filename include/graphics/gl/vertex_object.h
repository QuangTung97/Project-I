#ifndef VERTEX_OBJECT_H
#define VERTEX_OBJECT_H

#include <graphics/abstract/object.h>
#include <GL/glew.h>
#include <vector>

namespace tung {

class VertexObject: public IVertexObject {
private:
    GLuint vbo_;
    GLuint vao_;
    friend class VertexObjectBuilder;

public:
    void bind() override;

    ~VertexObject() override;
};

class VertexObjectBuilder: public IVertexObjectBuilder {
private:
    int element_count_ = 0;

    struct Attribute {
        std::string name_;
        const float *data_;
        int dimension_count_;
        int element_count_;
        int offset_ = 0;
    };

    std::vector<Attribute> attributes_;

public:
    void clear() override;

    void add_attribute(const std::string& name,
            const float *data, int dimension_count,
            int element_count) override;

    IVertexObjectPtr build(
            const std::unordered_map<std::string, int>& locations
        ) override;

    ~VertexObjectBuilder() override;
};

} // namespace tung

#endif
