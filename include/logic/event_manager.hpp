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
            const EventListener& listener) override;

    void remove_listener(IEventType& event_type,
            const EventListener& listener) override;

    void trigger(IEventData& event) override;

    void queue(IEventData& event) override;

    void update();

    virtual ~EventManager() {}
};

} // namespace tung

#endif
