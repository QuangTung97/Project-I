#ifndef LOGIC_EVENT_MANAGER_HPP
#define LOGIC_EVENT_MANAGER_HPP

#include "abstract/event_manager.hpp"
#include <unordered_map>
#include <vector>
#include <list>

namespace tung {

class EventManager: public IEventManager {
private:
    typedef std::vector<EventListener> ListenerList;
    typedef std::unordered_map<IEventType *, ListenerList> 
        ListenerMap;
    typedef std::list<IEventDataPtr> EventQueue;

    EventQueue event_queue_;

    ListenerMap listener_map_;

public:
    EventManager() = default;

    void add_listener(IEventType& event_type,
            EventListener listener) override {
        listener_map_[&event_type].push_back(listener);
    }

    void trigger(IEventData& event) override {
        for (auto& listener: 
                listener_map_[&event.get_event_type()]) {
            listener(event);
        }
    }

    void queue(IEventData& event) override {
        event_queue_.push_back(event.clone());
    }

    void update();

    virtual ~EventManager() {}
};

} // namespace tung

#endif
