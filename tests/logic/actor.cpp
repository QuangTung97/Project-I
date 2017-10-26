#include <gmock/gmock.h>
#include <logic/actor.hpp>

using namespace tung;

class ActorComponent1: public ActorComponent {
public:
    ActorComponentId get_id() const override {
        return ActorComponentId::TEST1;
    }

    float x, y;
};

class ActorComponent2: public ActorComponent {
public:
    ActorComponentId get_id() const override {
        return ActorComponentId::TEST2;
    }

    double width, height;
};

TEST(Actor, get_component) {
    auto actor = std::make_shared<Actor>(100);
    auto com1 = std::make_shared<ActorComponent1>();
    auto com2 = std::make_shared<ActorComponent2>();
    com1->x = 100;
    com1->y = 20;
    com2->width = 10;
    com2->height = 15;

    actor->add_component(com1);
    actor->add_component(com2);

    auto comp1 = actor->get_component<ActorComponent1>(
        ActorComponentId::TEST1
    ).lock();

    ASSERT_EQ(comp1->x, 100);
    ASSERT_EQ(comp1->y, 20);

    auto null = actor->get_component<ActorComponent>(
        ActorComponentId::TEST3
    ).lock();
    ASSERT_EQ(null, nullptr);

    actor->shutdown();
}