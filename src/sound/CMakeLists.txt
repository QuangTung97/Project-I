project (sound)

add_library(sound
    sound.cpp
)

target_link_libraries(sound
    fmod
)
