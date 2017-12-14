#ifndef LOGIC_ABSTRACT_LOOP_PROCESS_HPP 
#define LOGIC_ABSTRACT_LOOP_PROCESS_HPP

#include "process.hpp"
#include <functional>

namespace tung {

// Process sẽ được gọi liên tục sau một khoảng thời gian. 
class LoopProcess: public Process {
private:
    const milliseconds duration_;
    const std::function<void()> function_;
    milliseconds elapsed_time_;

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        if (elapsed_time_ >= duration_) {
            elapsed_time_ = 0ms;
            function_();
        }
    }

public:
    // Constructor
    // @duration: Khoảng thời gian giữa hai lần gọi 
    // @func: Hàm sẽ được gọi
    LoopProcess(milliseconds duration, std::function<void()> func)
    : duration_{duration}, function_{std::move(func)} {}
};

} // namespace tung

#endif