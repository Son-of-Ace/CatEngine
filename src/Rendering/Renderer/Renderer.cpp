#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Renderer.hpp"
#include "../../Utils/FileUtils.hpp"

void Renderer::Init() {
  images = GetAnimationFrames("../textures/Animations/FunnyCat");

  shader.emplace("../shaders/vertex.glsl", "../shaders/fragment.glsl");
  shader->Use();

  // clang-format off
    // Square
    constexpr float vertices[] = {
        // Positions             // Colors              // UV
        -1.0f, -1.0f, 0.0f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,      1.0f, 1.0f, 0.0f,      0.0f, 1.0f,
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
  // clang-format on

  // Buffers
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // UV
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Texture Calls
  for (const std::string& imagePath : images) {
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    const GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    textures.push_back(texture);
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glClearColor(r, g, b, 1.0f);
}

void Renderer::Render() {
  shader->Use();

  float time = glfwGetTime();
  float fps = 10.0f;

  int frame = static_cast<int>(time * fps) % textures.size();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[frame]);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
