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
    drawable_factory.cpp
    text_factory.cpp
)

target_link_libraries(graphics-gl
    graphics-image
    freetype
    GL GLEW glfw
)
