cmake_minimum_required(VERSION 3.2)

project(ProjectI)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

link_directories(lib)

add_subdirectory(src)
add_executable(main src/root.cpp)
target_link_libraries(main src)

# For testing
enable_testing()
add_subdirectory(tests)
