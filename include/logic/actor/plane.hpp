#ifndef LOGIC_PLANE_COMPONENT_HPP
#define LOGIC_PLANE_COMPONENT_HPP

#include <logic/abstract/process.hpp>
#include <logic/basic/process_manager.hpp>
#include <logic/abstract/event_manager.hpp>
#include "base.hpp"
#include "component.hpp"

namespace tung {
namespace actor {

class Plane;

class FlyProcess: public Process {
private:
    Plane& owner_;

public:
    FlyProcess(Plane& owner): owner_{owner} {}

protected:
    void on_init() override;

    void on_update(milliseconds dt) override;

    void on_success() override;

    void on_fail() override;
};

class WaitToDestroyPlaneProcess: public Process {
private:
    Plane& owner_;
    const milliseconds wait_time_;
    milliseconds elapsed_time_;

public:
    WaitToDestroyPlaneProcess(Plane& owner, milliseconds wait_time)
    : owner_{owner}, wait_time_{wait_time} {}

protected:
    void on_init() override;

    void on_update(milliseconds dt) override;
    
    void on_success() override;
};

class Plane: public Component {
private:
    friend class FlyProcess;
    friend class WaitToDestroyPlaneProcess;

    IEventManager& event_manager_;
    ProcessManager& process_manager_;
    float x_, y_, dx_ = 0.0f;
    const float velocity_;
    const bool is_fighter_ = true;
    const float max_distance_ = 4;

    StrongProcessPtr fly_process_;
    StrongProcessPtr destroy_plane_;

public:
    static const ComponentId COMPONENT_ID;

    Plane(IEventManager& manager, ProcessManager& process_manager,
        float x, float y, float velocity, bool is_fighter);

    ComponentId get_id() const override {
        return ComponentId::PLANE;
    }

    void start_fly();

    void end_fly();

    void explode();
};

} // namespace actor
} // namespace tung

#endif