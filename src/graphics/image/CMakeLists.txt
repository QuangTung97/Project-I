project(graphics-image)

add_library(graphics-image 
    png.cpp
    font.cpp
)

target_link_libraries(graphics-image
    png
)
