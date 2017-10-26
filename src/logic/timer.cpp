#include <logic/timer.hpp>

namespace tung {

EventType<5000> GAME_PAUSE;
EventType<5001> GAME_RESUME;

Timer::Timer(IEventManager& manager)
: manager_{manager} {
    auto pause = [this](const IEventData& event) {
        prev_timestamp_ = steady_clock::now();
    };
    pause_listener_ = pause;

    auto resume = [this](const IEventData& event) {
        auto delta = steady_clock::now() - prev_timestamp_;
        delay_ += delta;
    };
    resume_listener_ = resume;

    manager.add_listener(GAME_PAUSE, pause_listener_);
    manager.add_listener(GAME_RESUME, resume_listener_);
}

TimePoint Timer::current_time() {
    return steady_clock::now() - delay_;
}

Timer::~Timer() {
    manager_.remove_listener(GAME_PAUSE, pause_listener_);
    manager_.remove_listener(GAME_RESUME, resume_listener_);
}

} // namespace tung