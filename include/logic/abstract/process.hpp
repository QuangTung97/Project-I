#ifndef LOGIC_ABSTRACT_PROCESS_HPP
#define LOGIC_ABSTRACT_PROCESS_HPP

#include <memory>

namespace tung {

class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;

class Process {
public:
    enum State {
        UNINITIALIZED = 0,
        REMOVED,
        RUNNING,
        PAUSED,
        SUCCEEDED,
        FAILED,
        ABORTED,
    };
    
private:
    friend class ProcessManager;

    State state_ = UNINITIALIZED;
    StrongProcessPtr child_;

    void set_state(State state) { state_ = state; }

public:
    Process() = default;

    virtual ~Process() {}

    void succeed() { set_state(SUCCEEDED); }

    void fail() { set_state(FAILED); }

    void pause() { set_state(PAUSED); }

    void resume() { set_state(RUNNING); }

    State get_state() const { return state_; }

    bool is_alive() const { return state_ == RUNNING || state_ == PAUSED; }

    bool is_dead() const {
        return state_ == SUCCEEDED || state_ == FAILED || state_ == ABORTED;
    }

    bool is_paused() const { return state_ == PAUSED; }

    void attach_child(StrongProcessPtr child) {
        child_ = std::move(child);
    }

    // release ownership of the child
    StrongProcessPtr remove_child() {
        return std::move(child_);
    }

protected:
    virtual void on_init() { state_ = RUNNING; }

    virtual void on_update(unsigned long delta_ms) = 0;

    virtual void on_success() {}

    virtual void on_fail() {}

    virtual void on_abort() { on_fail(); }
    
};

} // namespace tung

#endif
