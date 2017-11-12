project(test_main)

add_executable(test_main
    main.cpp
    logic/event.cpp
    logic/process.cpp
    logic/actor.cpp
    logic/actor_collision.cpp
)

target_link_libraries(test_main 
    src
    gmock_main
    pthread
)

add_test(NAME TestMain COMMAND test_main)
