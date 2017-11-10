project(view)

add_library(view 
    view.cpp
    image_view.cpp
    text_view.cpp
)

target_link_libraries(view
    graphics-gl
)
