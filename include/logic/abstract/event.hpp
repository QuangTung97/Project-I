#ifndef LOGIC_ABSTRACT_EVENT_HPP
#define LOGIC_ABSTRACT_EVENT_HPP

#include <functional>
#include <memory>
#include "timer.hpp"

// Base Class cho tất cả các event trong hệ thống
namespace tung {

// Base Class cho tất cả các Type ứng với mỗi loại event 
struct IEventType {
    // Trả về giá trị type id của event
    virtual int get_id() const = 0;
};

struct IEventData;

typedef std::unique_ptr<IEventData> IEventDataPtr;

// Interface cho các event trong hệ thống 
struct IEventData {
    // Trả về kiểu event 
    virtual IEventType& get_event_type() const = 0;

    // Trả về thời điểm event xảy ra 
    virtual TimePoint get_time_point() const = 0;

    // Sinh ra một Event khác giống event hiện tại 
    virtual IEventDataPtr clone() const = 0;

    // Destructor 
    virtual ~IEventData() {}
};

// ---------------------------------------------------
// Thiết lập một tập các class để có chức năng 
// tương tự std::function<const IEventData& event>
// Nhưng có toán tử so sánh. 
// ---------------------------------------------------
struct ICallable {
    virtual void call(const IEventData& event) = 0;

    virtual ~ICallable() {}
};

template<typename Func>
class Callable: public ICallable {
private:
    const Func func_;

public:
    Callable(Func func): func_{func} {}

    void call(const IEventData& event) override {
        func_(event);
    }

    virtual ~Callable() {}
};

class EventListener {
private:
    std::shared_ptr<ICallable> func_ = nullptr;

public:
    EventListener() {}

    template<typename Func>
    EventListener(Func func) {
        func_ = std::make_shared<Callable<Func>>(func);
    }

    template<typename Func>
    EventListener& operator = (Func func) {
        func_ = std::make_shared<Callable<Func>>(func);
        return *this;
    }

    EventListener& operator = (const EventListener& other) {
        func_ = other.func_;
        return *this;
    }

    void operator () (const IEventData& event) {
        func_->call(event);
    }

    bool operator == (const EventListener& listener) {
        return this->func_ == listener.func_;
    }
};

} // namespace tung

#endif
