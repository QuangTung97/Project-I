#include <graphics/gl/null_drawable.hpp>

namespace tung {

NullDrawable::NullDrawable() 
    : model_matrix_(1.0) 
{}

const glm::mat4& NullDrawable::model_matrix() const {
    return model_matrix_;
}

} // namespace tung
