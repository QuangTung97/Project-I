#ifndef LOGIC_ABSTRACT_EVENT_MANAGER_HPP
#define LOGIC_ABSTRACT_EVENT_MANAGER_HPP

#include "event.hpp"

namespace tung {

// Interface của bộ quản lý sự kiện trong game. 
struct IEventManager {
    // @event_type: Kiểu sự kiện. 
    // @listener: Listener sẽ được thêm. 
    // Thêm một listener (Bộ lắng nghe)
    virtual void add_listener(IEventType& event_type,
            const EventListener& listener) = 0;

    // @event_type: Kiểu sự kiện. 
    // @listener: Listener sẽ được xóa. 
    virtual void remove_listener(IEventType& event_type,
            const EventListener& listener) = 0;

    // Gửi một thông điệp ngay lập tức đến các listener. 
    // @event: event sẽ được gửi. 
    virtual void trigger(IEventData& event) = 0;

    // Gửi một thông điệp ngay đến các listener. 
    // @event: event sẽ được gửi. 
    // Thông điệp sẽ được thêm vào hàng đợi. và lần lượt lấy ra ở mỗi lần update. 
    virtual void queue(IEventData& event) = 0;

    // Xử lý các thông điệp trong hàng đợi. 
    virtual void update() = 0;

    // Destructor
    virtual ~IEventManager() {}
};

} // namespace tung

#endif
