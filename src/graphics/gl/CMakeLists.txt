project(graphics-gl)


add_library(graphics-gl
    glfw.cpp
    drawable.cpp
    opengl_info.cpp
    shader_program.cpp
    ui_shader_program.cpp
    vertex_object.cpp
)

target_link_libraries(graphics-gl
    GL GLEW glfw
)
