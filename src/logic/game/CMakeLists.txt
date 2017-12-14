project(logic-game)

add_library(logic-game
    plane.cpp
    cannon.cpp
    bullet.cpp
    manager.cpp
    start_state.cpp
    playing_state.cpp
    end_state.cpp
    level_manager.cpp
)

target_link_libraries(logic-game
    logic-actor
)