#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <print>

#include "Application.hpp"
#include "../Rendering/Renderer/Renderer.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void Application::Run() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return;
  }

  window = glfwCreateWindow(2560, 1440, "Hello, World", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    return;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Renderer renderer;
  renderer.Init();

  std::print("Hello6{}", " ");

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
