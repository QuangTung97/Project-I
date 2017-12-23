#ifndef LOGIC_ABSTRACT_LOOP_PROCESS_HPP 
#define LOGIC_ABSTRACT_LOOP_PROCESS_HPP

#include "process.hpp"
#include <functional>

namespace tung {

// Process sẽ đợi một khoảng thời gian
// Thường sử dụng để làm cha của một process khác 
class WaitProcess: public Process {
private:
    const milliseconds duration_;
    milliseconds elapsed_time_;

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        if (elapsed_time_ >= duration_) {
            succeed();
        }
    }

public:
    // Constructor
    // @duration: Khoảng thời gian chờ 
    WaitProcess(milliseconds duration): duration_{duration} {}
};

} // namespace tung

#endif