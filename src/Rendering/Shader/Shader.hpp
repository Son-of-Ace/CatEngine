#pragma once

#include <string>

class Shader {
public:
    unsigned int vertexShader, fragmentShader, shaderProgram;

    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void Use();
};
