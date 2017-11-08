project(logic)

add_subdirectory(basic)
add_subdirectory(actor)
add_subdirectory(system)
add_subdirectory(game)

add_library(logic
    game_logic.cpp
)

target_link_libraries(logic 
    logic-basic
    logic-actor
    logic-system
    logic-game
)
