#include <glad/glad.h>

#include "Shader.hpp"
#include "../../Utils/ShaderUtils.hpp"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    const std::string vertexSource = LoadShader(vertexPath);
    const std::string fragmentSource = LoadShader(fragmentPath);

    const char *vertexShaderSource = vertexSource.c_str();
    const char *fragmentShaderSource = fragmentSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Vertex shader compilation failed: ") + infoLog);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Fragment shader compilation failed: ") + infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Shader program linking failed: ") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


Shader::~Shader() { glDeleteProgram(shaderProgram); }
void Shader::Use() { glUseProgram(shaderProgram); }
