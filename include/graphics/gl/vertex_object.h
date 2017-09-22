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
    struct TextureBind {
        unsigned active_number_;
        int location_;
        ITexturePtr texture_;
    };

    GLuint vbo_;
    GLuint vao_;
    std::vector<unsigned short> indices_;
    std::vector<TextureBind> textures_;

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
    std::vector<VertexObject::TextureBind> textures_;

    struct Attribute {
        int location_;
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

    void add_texture(
            unsigned int active_number,
            const std::string& name,
            const ITexturePtr& texture) override;

    void set_indices(
            const std::vector<unsigned short>& indices) override;

    IVertexObjectPtr build() override;

    virtual ~VertexObjectBuilder();
};

} // namespace tung

#endif
