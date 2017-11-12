#include <logic/actor/collision.hpp>
#include <gmock/gmock.h>

using namespace tung::actor;

TEST(collision_rectangle_circle, inside_rectangle) {
    float rx = 10;
    float ry = 20;
    float width = 40;
    float height = 24;
    float cx = 30;
    float cy = 32;
    float radius = 0;
    ASSERT_TRUE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));
}

TEST(collision_rectangle_circle, outside_corners) {
    float rx = 10;
    float ry = 20;
    float width = 40;
    float height = 24;
    float cx = 40;
    float cy = 42;
    float radius = 15;
    ASSERT_TRUE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));

    radius = 14;
    ASSERT_FALSE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));
}

TEST(collision_rectangle_circle, outside_width) {
    float rx = 10;
    float ry = 20;
    float width = 40;
    float height = 24;
    float cx = 40;
    float cy = 13;
    float radius = 10;
    ASSERT_TRUE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));

    radius=9;
    ASSERT_FALSE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));
}

TEST(collision_rectangle_circle, outside_height) {
    float rx = 10;
    float ry = 20;
    float width = 40;
    float height = 24;
    float cx = 11;
    float cy = 42;
    float radius = 10;
    ASSERT_TRUE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));

    radius = 9;
    ASSERT_FALSE(is_rectangle_circle_collided(
        rx, ry, width, height, 
        cx, cy, radius
    ));
}

TEST(collision_two_rectangle, normal) {
    float x1 = 10;
    float y1 = 12;
    float width1 = 40;
    float height1 = 24;
    float x2 = 45;
    float y2 = 34;
    float width2 = 30;
    float height2 = 20;

    ASSERT_TRUE(is_two_rectangle_collided(
        x1, y1, width1, height1,
        x2, y2, width2, height2
    ));

    width2 = 29;
    height2 = 20;
    ASSERT_FALSE(is_two_rectangle_collided(
        x1, y1, width1, height1,
        x2, y2, width2, height2
    ));

    width2 = 30;
    height2 = 19;
    ASSERT_FALSE(is_two_rectangle_collided(
        x1, y1, width1, height1,
        x2, y2, width2, height2
    ));
}