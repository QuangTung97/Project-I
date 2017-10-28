#ifndef LOGIC_PLANE_COMPONENT_HPP
#define LOGIC_PLANE_COMPONENT_HPP

#include "actor_component.hpp"
#include <logic/abstract/process.hpp>
#include <sound/abstract/sound.hpp>

namespace tung {

class PlaneComponent: public ActorComponent {
protected:
    float x_, y_;
    bool is_fighter = true;
    StrongProcessPtr fly_process_;
    ISoundPtr fly_sound_;

public:
    ActorComponentId get_id() const override {
        return ActorComponentId::PLANE;
    }

    void start_flying();

    void stop_flying();
};

} // namespace tung

#endif