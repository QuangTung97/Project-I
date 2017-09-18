project(graphics)

add_subdirectory(image)

add_library(graphics 
    glfw.cpp
    opengl_info.cpp
    shader_program.cpp
    ui_shader_program.cpp
)

target_link_libraries(graphics
    graphics-image
    GL GLEW glfw
)
