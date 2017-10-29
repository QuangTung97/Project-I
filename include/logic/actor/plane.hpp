#ifndef LOGIC_PLANE_COMPONENT_HPP
#define LOGIC_PLANE_COMPONENT_HPP

#include <logic/abstract/process.hpp>
#include <sound/abstract/sound.hpp>
#include "base.hpp"
#include "component.hpp"

namespace tung {
namespace actor {

class Plane: public Component {
protected:
    float x_, y_;
    bool is_fighter = true;
    StrongProcessPtr fly_process_;
    ISoundPtr fly_sound_;

public:
    ComponentId get_id() const override {
        return ComponentId::PLANE;
    }

    void start_flying();

    void stop_flying();
};

} // namespace actor
} // namespace tung

#endif