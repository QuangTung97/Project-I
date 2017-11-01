#include <logic/actor/sprite.hpp>

namespace tung {
namespace actor {

void SpriteElement::start() {
    drawable_->use_sprite(0);
}

} // namespace actor
} // namespace tung