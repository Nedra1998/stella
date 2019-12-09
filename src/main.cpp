#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.hpp"

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = NULL;
  window = glfwCreateWindow(500, 500, "stella", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    std::cerr << "Failed to open GLFW window\n";
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cerr << "Failed to load OpenGL functions\n";
    return -2;
  }
  glViewport(0, 0, 500, 500);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);

  glm::vec3 view_pos = glm::vec3(0.0, 0.0, 3.0f);
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, -view_pos);

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f),
      (float)500/ (float)500, 0.1f, 100.0f);

  astri::Shader shader("../shaders/vs.glsl", "../shaders/fs.glsl");
  shader.use();
  shader.set("uLightPost", glm::vec3(-100.0, 0.0, 50.0));
  shader.set("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
  shader.set("uView", view);
  shader.set("uProjection", projection);
  shader.set("uViewPos", view_pos);

  glClearColor(0.149f, 0.196f, 0.219f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
