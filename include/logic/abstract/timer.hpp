#ifndef LOGIC_ABSTRACT_TIMER_HPP
#define LOGIC_ABSTRACT_TIMER_HPP

#include <chrono>

using namespace std::chrono;

namespace tung {

typedef steady_clock::time_point TimePoint;

// Quản lý thời gian của game
// Thời gian của game là thời gian có tính đến việc game tạm dừng
struct ITimer {
    // Trả về thời điểm hiện tại 
    virtual TimePoint current_time() = 0;
    
    // Destructor
    virtual ~ITimer() {}
};

} // namespace tung

#endif
