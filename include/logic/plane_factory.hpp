#ifndef LOGIC_PLANE_FACTORY_HPP
#define LOGIC_PLANE_FACTORY_HPP

#include <logic/actor.hpp>

namespace tung {

class PlaneFactory {
private:

public:
    WeakActorPtr new_plane(bool is_fighter = true);
};

} // namespace tung

#endif