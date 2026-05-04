cmake_minimum_required(VERSION 4.2)
project(BrawlEngine)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(BrawlEngine main.cpp)

target_link_libraries(BrawlEngine
        OpenGL::GL
        glfw
        GLEW::GLEW
)
