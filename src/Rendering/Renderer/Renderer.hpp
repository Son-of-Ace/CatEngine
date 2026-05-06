#pragma once

#include "../Shader/Shader.hpp"

#include <optional>

class Renderer {
 public:
  void Init();
  void Render();

 private:
  std::optional<Shader> shader;

  // GPU Buffers
  unsigned int VBO = 0;
  unsigned int EBO = 0;
  unsigned int VAO = 0;

  // Textures
  int width = 0, height = 0, nrChannels = 0;
  unsigned char* data = nullptr;

  unsigned int texture = 0;

  // RGB Background Colors
  const float r = 0;
  const float g = 209 / 255.0f;
  const float b = 255 / 255.0f;
};
