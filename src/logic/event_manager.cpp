#include <logic/event_manager.hpp>
#include <algorithm>

namespace tung {

void EventManager::add_listener(IEventType& event_type,
        const EventListener& listener) {
    listener_map_[&event_type].push_back(listener);
}

void EventManager::remove_listener(IEventType& event_type,
        const EventListener& listener) {
    auto& list = listener_map_[&event_type];
    auto it = std::remove(list.begin(), list.end(), listener);
    list.erase(it, list.end());
}

void EventManager::trigger(IEventData& event) {
    for (auto& listener: 
            listener_map_[&event.get_event_type()]) {
        listener(event);
    }
}

void EventManager::queue(IEventData& event) {
    event_queue_.push_back(event.clone());
}

void EventManager::update() {
    while (!event_queue_.empty()) {
        auto event = std::move(event_queue_.front());
        event_queue_.pop_front();
        this->trigger(*event);
    }
}

} // namespace tung
