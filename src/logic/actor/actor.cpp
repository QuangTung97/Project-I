#include <logic/actor/actor.hpp>
#include <logic/actor/component.hpp>

namespace tung {
namespace actor {

ActorId IdGenerator::last_ = 0;

ActorId IdGenerator::new_id() {
    // Tăng giá trị last 
    // và trả về 
    return ++last_;
}

void Actor::add_component(StrongComponentPtr component) {
    // Lấy id của component 
    ComponentId id = component->get_id();
    // Thiết lập owner là chính actor này 
    component->set_owner(shared_from_this());
    // Thêm nó vào từ điển các component 
    components_[id] = std::move(component);
}

} // namespace actor
} // namespace tung
