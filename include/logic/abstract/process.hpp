#ifndef LOGIC_ABSTRACT_PROCESS_HPP
#define LOGIC_ABSTRACT_PROCESS_HPP

#include <memory>
#include <chrono>

using namespace std::chrono;

namespace tung {

//-------------------------------------------------------
// Process là một class tiện ích của hệ thống 
// Giúp giả lập những quá trình xảy ra giống như nó chạy 
// song song 
// Ví dụ: máy bay bay, đạn bay, hiệu ứng nổ. 
// Process con là process mà sẽ được kích hoạt ngay sau 
// khi process cha kết thúc thành công. 
//-------------------------------------------------------
class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;

class Process {
public:
    // Trạng thái của một tiến trình. 
    enum State {
        UNINITIALIZED = 0, // Chưa được khởi tạo 
        // REMOVED, // Đã được xóa khỏi danh sách các tiến trình 
        RUNNING,  // Đang chạy 
        PAUSED, // Đã được tạm dừng 
        SUCCEEDED, // Đã kết thúc (Kết thúc thành công)
        FAILED, // Đã kết thúc (Kết thúc theo cách thất bại)
        ABORTED, // Đã bị hủy bởi hệ thống. 
    };
    
private:
    friend class ProcessManager;

    State state_ = UNINITIALIZED;
    StrongProcessPtr child_;
    bool is_attached_ = false;

    void set_state(State state) { state_ = state; }

public:
    // Constructor 
    Process() = default;

    // Destructor
    virtual ~Process() {}

    // Thiết lập trạng thái liệu process có nằm trong danh sách các tiến trình 
    // @value: Đúng nếu nằm trong danh sách. 
    void set_attached(bool value) {
        is_attached_ = value;
    }

    // Trả về liệu rằng process có nằm trong danh sách tiến trình. 
    bool is_attached() {
        return is_attached_;
    }

    // Chuyển process về trạng thái ban đầu. 
    void reset() { set_state(UNINITIALIZED); }

    // Chuyển trạng thái process sang trạng thái kết thúc và thành công 
    void succeed() { set_state(SUCCEEDED); }

    // Chuyển trạng thái process sang trạng thái kết thúc và thất bại 
    void fail() { set_state(FAILED); }

    // Chuyển trạng thái process sang trạng thái tạm dừng
    void pause() { set_state(PAUSED); }

    // Chuyển trạng thái process sang trạng thái đang chạy 
    void resume() { set_state(RUNNING); }

    // Trả về trạng thái của process. 
    State get_state() const { return state_; }

    // Trả về liệu process có còn sống hay không 
    bool is_alive() const { return state_ == RUNNING || state_ == PAUSED; }

    // Trả về liệu process đã kết thúc hay không. 
    bool is_dead() const {
        return state_ == SUCCEEDED || state_ == FAILED || state_ == ABORTED;
    }

    // Trả về liệu rằng process có đang tạm dừng hay không 
    bool is_paused() const { return state_ == PAUSED; }

    // Gắn một process con. 
    void attach_child(StrongProcessPtr child) {
        child_ = std::move(child);
    }

    // release ownership of the child
    StrongProcessPtr remove_child() {
        return std::move(child_);
    }

protected:
    // Hàm sẽ được gọi khi kết thúc trạng thái chưa được khỏi tạo 
    virtual void on_init() { state_ = RUNNING; }

    // Hàm sẽ được gọi liên tục, theo từng frame của hệ thống. 
    // @dt: Khoảng thời gian (theo milli giây) giữa hai lần gọi update. 
    virtual void on_update(milliseconds dt) = 0;

    // Hàm sẽ được gọi khi chuyển sang trại thái kết thúc và thành công 
    virtual void on_success() {}

    // Hàm sẽ được gọi khi chuyển sang trại thái kết thúc và thất bại 
    virtual void on_fail() {}

    // Hàm sẽ được gọi khi chuyển sang trại thái bị hủy 
    virtual void on_abort() { on_fail(); }
};

} // namespace tung

#endif
