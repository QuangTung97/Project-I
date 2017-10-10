#ifndef LOGIC_ABSTRACT_TIMER_HPP
#define LOGIC_ABSTRACT_TIMER_HPP

#include <chrono>

using namespace std::chrono;

namespace tung {

typedef steady_clock::time_point TimePoint;

struct ITimer {
    virtual TimePoint current_time() = 0;
    
    virtual ~ITimer() {}
};

} // namespace tung

#endif
