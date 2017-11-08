#ifndef LOGIC_SYSTEM_GRAPHICS_HPP
#define LOGIC_SYSTEM_GRAPHICS_HPP

#include <logic/actor/graphics_image.hpp>
#include <logic/abstract/event.hpp>
#include <logic/abstract/event_manager.hpp>

namespace tung {
namespace system {

class Graphics {
private:
    IEventManager& event_manager_;
    EventListener actor_created_listener_;
    EventListener actor_destroy_listener_;
    EventListener actor_move_listener_;

    typedef std::weak_ptr<actor::GraphicsImage> GraphicsImageWeakPtr;
    std::unordered_map<actor::ActorId, GraphicsImageWeakPtr> 
        graphics_image_components_;
public:
    Graphics(IEventManager& event_manager);

    ~Graphics();
};

} // namespace system
} // namespace tung

#endif