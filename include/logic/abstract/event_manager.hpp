#ifndef LOGIC_ABSTRACT_EVENT_MANAGER_HPP
#define LOGIC_ABSTRACT_EVENT_MANAGER_HPP

#include "event.hpp"

namespace tung {

struct IEventManager {
    virtual void add_listener(IEventType& event_type,
            const EventListener& listener) = 0;

    virtual void remove_listener(IEventType& event_type,
            const EventListener& listener) = 0;

    virtual void trigger(IEventData& event) = 0;

    virtual void queue(IEventData& event) = 0;

    virtual ~IEventManager() {}
};

} // namespace tung

#endif
