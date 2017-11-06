project(logic-factory)

add_library(logic-factory
    plane.cpp
)

target_link_libraries(logic-factory
    logic-actor
)