project(logic-actor)

add_library(logic-actor
    actor.cpp
    component.cpp
    events.cpp
    collision.cpp
    graphics_image.cpp
    sprite.cpp
    sound.cpp
)

target_link_libraries(logic-actor
    graphics-color
)