#include <logic/basic/event_manager.hpp>
#include <algorithm>

namespace tung {

void EventManager::add_listener(IEventType& event_type,
        const EventListener& listener) {
    // Thêm một listenter vào danh sách 
    listener_map_[&event_type].push_back(listener);
}

void EventManager::remove_listener(IEventType& event_type,
        const EventListener& listener) {
    // Xóa một listener khỏi danh sách 
    auto& list = listener_map_[&event_type];
    auto it = std::remove(list.begin(), list.end(), listener);
    list.erase(it, list.end());
}

void EventManager::trigger(IEventData& event) {
    // Duyệt qua từng listener ứng với kiểu sự kiện 
    for (auto& listener: 
            listener_map_[&event.get_event_type()]) {
        // Gọi hàm listener 
        listener(event);
    }
}

void EventManager::queue(IEventData& event) {
    // Thêm event vào hàng đợi
    event_queue_.push_back(event.clone());
}

void EventManager::update() {
    // Liên tục lấy các phần tử trong hàng đợi 
    while (!event_queue_.empty()) {
        auto event = std::move(event_queue_.front());
        event_queue_.pop_front();
        // Và gửi sự kiện đi 
        this->trigger(*event);
    }
}

} // namespace tung
