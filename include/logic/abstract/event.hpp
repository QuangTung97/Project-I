#ifndef LOGIC_ABSTRACT_EVENT_HPP
#define LOGIC_ABSTRACT_EVENT_HPP

#include <functional>
#include <memory>
#include "timer.hpp"

namespace tung {

struct IEventType {
    virtual int get_id() const = 0;
};

struct IEventData;

typedef std::unique_ptr<IEventData> IEventDataPtr;

struct IEventData {
    virtual IEventType& get_event_type() const = 0;

    virtual TimePoint get_time_point() const = 0;

    virtual IEventDataPtr clone() const = 0;

    virtual ~IEventData() {}
};

typedef std::function<void(const IEventData& event)> EventListener;

} // namespace tung

#endif
