#ifndef GAME_LOGIC_ACTOR_COMPONENT_HPP
#define GAME_LOGIC_ACTOR_COMPONENT_HPP

#include <memory>
#include "base.hpp"
#include "component_id.hpp"

namespace tung {
namespace actor {

//------------------------------------------------------
// Sử dụng kiến trúc hướng thành phần 
// (Component Architecture)
//------------------------------------------------------

// Chứa thông tin của một component
class Component: public std::enable_shared_from_this<Component> {
private:
    StrongActorPtr owner_;
    friend class Actor;

public:
    // Trả về id của component này 
    virtual ComponentId get_id() const = 0;

    // Destructor này 
    virtual ~Component() {}

    // Thiết lập con trỏ đến actor chứa component này. 
    void set_owner(StrongActorPtr owner);

    // Trả về actor id tương ứng.
    ActorId get_actor_id() const;
};

} // namespace actor
} // namespace tung

#endif