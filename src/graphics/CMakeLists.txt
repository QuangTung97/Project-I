project(graphics)

add_library(graphics 
    glfw.cpp
    opengl_info.cpp
    shader_program.cpp
)

target_link_libraries(graphics
    GL GLEW glfw
)
