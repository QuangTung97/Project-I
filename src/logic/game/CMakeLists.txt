project(logic-game)

add_library(logic-game
    plane.cpp
    manager.cpp
    start_state.cpp
)

target_link_libraries(logic-game
    logic-actor
)