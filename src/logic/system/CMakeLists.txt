project(logic-system)

add_library(logic-system
    collision.cpp
    sound.cpp
    sprite.cpp
    graphics.cpp
)

target_link_libraries(logic-system
    logic-actor
)