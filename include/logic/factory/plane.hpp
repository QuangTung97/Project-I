#ifndef LOGIC_FACTORY_PLANE_HPP
#define LOGIC_FACTORY_PLANE_HPP

#include <logic/actor/actor.hpp>
#include <logic/abstract/event_manager.hpp>
#include <logic/basic/process_manager.hpp>
#include <sound/abstract/sound.hpp>

namespace tung {
namespace factory {

class Plane {
private:
    IEventManager& event_manager_;
    ISoundManager& sound_manager_;
    ProcessManager& process_manager_;

public:
    Plane(IEventManager& event_manager, 
        ISoundManager& sound_manager,
        ProcessManager& process_manager)
    : event_manager_{event_manager}, 
    sound_manager_{sound_manager},
    process_manager_{process_manager} {}

    actor::ActorId new_plane(bool is_fighter = true);
};

} // namespace factory
} // namespace tung

#endif