#ifndef LOGIC_EVENT_HPP
#define LOGIC_EVENT_HPP

#include <logic/abstract/event.hpp>

namespace tung {

// Lớp cơ sở của loại sự kiện 
// Id: Id của sự kiện 
template<int Id>
class EventType: public IEventType {
public:
    int get_id() const override { return Id; }

    // Destructor
    virtual ~EventType() {}
};

// Lớp cơ sở của sự kiện. 
class EventData: public IEventData {
protected:
    const TimePoint time_point_;
    IEventType& event_type_;

public:
    // Constructor
    // @time_point: Thời điểm xảy ra sự kiện. 
    // @event_type: Loại sự kiện
    EventData(TimePoint time_point, IEventType& event_type)
        : time_point_{time_point}, event_type_{event_type} {}

    IEventType& get_event_type() const override { 
        return event_type_;
    }

    TimePoint get_time_point() const override {
        return time_point_;
    }

    IEventDataPtr clone() const override {
        return std::make_unique<EventData>(time_point_, event_type_);
    }

    // Destructor
    virtual ~EventData() {}
};


} // namespace tung

#endif
