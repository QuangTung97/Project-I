project(view)

add_library(view 
    view.cpp
    text.cpp
)

target_link_libraries(view
    freetype
)
