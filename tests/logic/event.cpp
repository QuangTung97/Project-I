#include <gmock/gmock.h>
#include <logic/event_manager.hpp>
#include <logic/event.hpp>

using namespace tung;

TEST(EventManager, normal) {
    EventType<1000> type1;
    auto time_point = steady_clock::now();
    EventData event_data(time_point, type1);

    int count_call = 0;

    auto func1 = [&](const IEventData& event) {
        count_call++;
        ASSERT_EQ(&event, &event_data);
    };

    EventListener listener1 = func1;

    EventManager manager;
    IEventManager &imanager = manager;

    imanager.add_listener(type1, listener1);
    manager.trigger(event_data);

    ASSERT_EQ(count_call, 1);
}

TEST(EventManager, remove_listener) {
    EventType<1000> type1;
    EventType<1001> type2;

    auto time_point = steady_clock::now();
    EventData event_data1(time_point, type1);
    EventData event_data2(time_point, type2);

    int count1 = 0;
    EventListener listener1 = [&](const IEventData& event) {
        count1++;
        ASSERT_EQ(&event, &event_data1);
    };

    int count2 = 0;
    EventListener listener2 = [&](const IEventData& event) {
        count2++;
        ASSERT_EQ(&event, &event_data2);
    };

    EventManager manager;
    manager.add_listener(type1, listener1);
    manager.add_listener(type2, listener2);
    manager.remove_listener(type2, listener2);

    manager.trigger(event_data1);
    manager.trigger(event_data2);

    ASSERT_EQ(count1, 1);
    ASSERT_EQ(count2, 0);
}

TEST(EventManager, queue) {
    EventType<1000> type1;
    EventType<1001> type2;

    auto time_point = steady_clock::now();
    EventData event_data1(time_point, type1);
    EventData event_data2(time_point, type2);

    int count1 = 0;
    EventListener listener1 = [&](const IEventData&) {
        count1++;
    };

    int count2 = 0;
    EventListener listener2 = [&](const IEventData&) {
        count2++;
    };

    EventManager manager;
    manager.add_listener(type1, listener1);
    manager.add_listener(type2, listener2);
    manager.remove_listener(type2, listener2);

    manager.queue(event_data1);
    manager.queue(event_data2);


    ASSERT_EQ(count1, 0);
    ASSERT_EQ(count2, 0);

    manager.update();

    ASSERT_EQ(count1, 1);
    ASSERT_EQ(count2, 0);
}
