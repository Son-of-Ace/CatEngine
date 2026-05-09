cmake_minimum_required(VERSION 4.2)
project(CatEngine)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(CatEngine
        src/main.cpp
        src/Application/Application.cpp
        src/Rendering/Renderer/Renderer.cpp
        src/Rendering/Shader/Shader.cpp
        external/glad/src/glad.c
)

target_include_directories(CatEngine PRIVATE
        external/glad/include
        external/stb
)

target_link_libraries(CatEngine
        OpenGL::GL
        glfw
)
