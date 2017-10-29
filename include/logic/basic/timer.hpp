#ifndef LOGIC_TIMER_HPP
#define LOGIC_TIMER_HPP

#include <logic/abstract/timer.hpp>
#include <logic/abstract/event_manager.hpp>
#include "event.hpp"

namespace tung {

extern EventType<5000> GAME_PAUSE;
extern EventType<5001> GAME_RESUME;

class Timer: public ITimer {
private:
    IEventManager& manager_;
    EventListener pause_listener_, resume_listener_;
    nanoseconds delay_ = 0ns;
    TimePoint prev_timestamp_;

public:
    Timer(IEventManager& manager);

    TimePoint current_time() override;

    virtual ~Timer();
};

} // namespace tung

#endif