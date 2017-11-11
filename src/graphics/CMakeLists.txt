project(graphics)

add_subdirectory(image)
add_subdirectory(gl)

add_library(graphics "")

add_library(graphics-color 
    color.cpp
)

target_link_libraries(graphics
    graphics-image
    graphics-gl
)
