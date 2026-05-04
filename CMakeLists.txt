cmake_minimum_required(VERSION 4.2)
project(HeavenEngine)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HeavenEngine
        src/main.cpp
        external/glad/src/glad.c
)

target_include_directories(HeavenEngine PRIVATE
        external/glad/include
)

target_link_libraries(HeavenEngine
        OpenGL::GL
        glfw
)
