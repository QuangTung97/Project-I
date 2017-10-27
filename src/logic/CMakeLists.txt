project(logic)

add_library(logic
    process_manager.cpp
    event_manager.cpp
    timer.cpp
    actor.cpp
    game_logic.cpp
    position_component.cpp
    collision_component.cpp
    sound_system.cpp
    collision_system.cpp
)
