project(graphics)

add_subdirectory(image)

add_subdirectory(gl)

add_library(graphics "")

target_link_libraries(graphics
    graphics-image
    graphics-gl
)
