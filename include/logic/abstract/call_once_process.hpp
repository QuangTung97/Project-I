#ifndef LOGIC_ABSTRACT_CALL_ONCE_PROCESS_HPP
#define LOGIC_ABSTRACT_CALL_ONCE_PROCESS_HPP

#include "process.hpp"
#include <functional>

namespace tung {

class CallOnceProcess: public Process {
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
            succeed();
        }
    }

    void on_success() override {
        function_();
    }

    void on_fail() override {
        function_();
    }

public:
    CallOnceProcess(milliseconds duration, std::function<void()> func)
    : duration_{duration}, function_{func} {}
};

} // namespace tung

#endif