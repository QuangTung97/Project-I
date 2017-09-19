#ifndef GRAPHICS_VERTEX_OBJECT_H
#define GRAPHICS_VERTEX_OBJECT_H

#include <memory>
#include <string>
#include <unordered_map>

namespace tung {

struct IVertexObject {
    virtual void bind() = 0;

    virtual ~IVertexObject() {}
};

typedef std::unique_ptr<IVertexObject> IVertexObjectPtr;

struct IVertexObjectBuilder {
    // Clear builder for the next build
    virtual void clear() = 0;

    virtual void add_attribute(
            const std::string& name,
            const float *data, int dimension_count,
            int element_count) = 0;

    virtual IVertexObjectPtr build(
            const std::unordered_map<std::string, int>& locations) = 0;

    virtual ~IVertexObjectBuilder() {}
};

} // namespace tung

#endif
