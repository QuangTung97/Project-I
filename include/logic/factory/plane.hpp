#ifndef LOGIC_FACTORY_PLANE_HPP
#define LOGIC_FACTORY_PLANE_HPP

#include <logic/actor/actor.hpp>

namespace tung {
namespace factory {

class Plane {
private:

public:
    actor::ActorId new_plane(bool is_fighter = true);
};

} // namespace factory
} // namespace tung

#endif