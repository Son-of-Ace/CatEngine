cmake_minimum_required(VERSION 4.2)
project(HeavenEngine)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(HeavenEngine
        src/main.cpp
        src/Application/Application.cpp
        src/Rendering/Renderer/Renderer.cpp
        src/Rendering/Shader/Shader.cpp
        external/glad/src/glad.c
)

target_include_directories(HeavenEngine PRIVATE
        external/glad/include
        external/stb
)

target_link_libraries(HeavenEngine
        OpenGL::GL
        glfw
)
