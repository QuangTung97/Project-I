project(graphics-gl)

add_library(graphics-gl
    glfw.cpp
    drawable.cpp
    sprite_drawable.cpp
    null_drawable.cpp
    opengl_info.cpp
    shader_program.cpp
    ui_shader_program.cpp
    simple_2d_shader.cpp
    vertex_object.cpp
    texture.cpp
)

target_link_libraries(graphics-gl
    GL GLEW glfw
)
