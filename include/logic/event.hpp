#ifndef LOGIC_EVENT_HPP
#define LOGIC_EVENT_HPP

#include "abstract/event.hpp"
#include <cassert>

namespace tung {

template<int Id>
class EventType: public IEventType {
public:
    int get_id() const override { return Id; }

    virtual ~EventType() {}
};


class EventData: public IEventData {
protected:
    const TimePoint time_point_;
    IEventType& event_type_;

public:
    EventData(TimePoint time_point, IEventType& event_type)
        : time_point_{time_point}, event_type_{event_type} {}

    IEventType& get_event_type() const override { 
        return event_type_;
    }

    TimePoint get_time_point() const override {
        return time_point_;
    }

    IEventDataPtr clone() const override {
        assert(false);
    }

    virtual ~EventData() {}
};


} // namespace tung

#endif
