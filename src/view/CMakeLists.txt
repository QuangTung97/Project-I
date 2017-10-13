project(view)

add_library(view 
    view.cpp
    text.cpp
    image_view.cpp
)

target_link_libraries(view
    freetype
    graphics-gl
)
