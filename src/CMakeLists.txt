project(src)

add_subdirectory(graphics)
# add_subdirectory(logic)
add_subdirectory(sound)
add_subdirectory(view)

add_library(src "")

target_link_libraries(src
    graphics
    view
    sound
)

