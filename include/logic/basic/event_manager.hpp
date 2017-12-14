#ifndef LOGIC_EVENT_MANAGER_HPP
#define LOGIC_EVENT_MANAGER_HPP

#include <logic/abstract/event_manager.hpp>
#include <unordered_map>
#include <vector>
#include <list>

namespace tung {

// Quản lý sự kiện 
class EventManager: public IEventManager {
private:
    typedef std::vector<EventListener> ListenerList;
    typedef std::unordered_map<IEventType *, ListenerList> 
        ListenerMap;
    typedef std::list<IEventDataPtr> EventQueue;

    EventQueue event_queue_;

    ListenerMap listener_map_;

public:
    // Constructor
    EventManager() = default;

    // Thêm một hàm lắng nghe sự kiện
    // @event_type: Loại sự kiện muốn lắng nghe
    // @listener: Hàm lắng nghe sự kiện 
    void add_listener(IEventType& event_type,
            const EventListener& listener) override;

    // Xóa một hàm lắng nghe sự kiện 
    // @event_type: Loại sự kiện muốn lắng nghe
    // @listener: Hàm lắng nghe sự kiện 
    void remove_listener(IEventType& event_type,
            const EventListener& listener) override;

    // Gửi một sự kiện, sự kiện được gửi đến các hàm lắng nghe ngay lập tức 
    // @event: Sự kiện muốn gửi. 
    void trigger(IEventData& event) override;

    // Gửi một sự kiện, sự kiện sẽ được đưa vào hàng đợi và 
    // gửi đến các hàm lắng nghe sau đó 
    // @event: Sự kiện muốn gửi. 
    void queue(IEventData& event) override;

    // Gửi các sự kiến đến các hàm lắng nghe từ hàng đợi. 
    void update() override;

    virtual ~EventManager() {}
};

} // namespace tung

#endif