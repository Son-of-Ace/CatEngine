#pragma once

#include <string>

class Renderer {
public:
    void Init();
    void Render();

private:
    // GPU Buffers
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int VAO = 0;

    // Shaders
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    unsigned int shaderProgram = 0;

    // Shader Sources
    std::string vertexSource;
    std::string fragSource;

    // Textures
    int width = 0, height = 0, nrChannels = 0;
    unsigned char *data = nullptr;

    unsigned int texture = 0;

    // RGB Background Colors
    const float r = 0;
    const float g = 209 / 255.0f;
    const float b = 255 / 255.0f;
};
