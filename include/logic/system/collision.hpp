#ifndef LOGIC_SYSTEM_COLLISION_HPP
#define LOGIC_SYSTEM_COLLISION_HPP

#include <logic/abstract/event_manager.hpp>
#include <logic/abstract/timer.hpp>
#include <logic/actor/collision.hpp>
#include <unordered_map>

namespace tung {
namespace system {

// Hệ thống kiểm soát va đập 
class Collision {
private:
    IEventManager& manager_;
    ITimer& timer_;
    EventListener actor_created_listener_;
    EventListener actor_destroy_listener_;
    EventListener actor_move_listener_;
    EventListener disable_listener_;
    EventListener enable_listener_;

    typedef std::weak_ptr<actor::Collision> WeakPtr;
    typedef std::unordered_map<actor::ActorId, WeakPtr> 
        ActorComponentMap;

    ActorComponentMap actor_components_;

public:
    // Constructor 
    Collision(IEventManager& manager, ITimer& timer);
    
    // Tính toán va đập giữa các object 
    void update();

    // Destructor
    ~Collision();
};

} // namespace system
} // namespace tung

#endif