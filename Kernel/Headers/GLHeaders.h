#pragma once

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define GLFW_INIT() \
  glfwInit(); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#define GLFW_TERMINATE() \
  glfwTerminate();

#define GLEW_INIT() \
  glewExperimental = GL_TRUE; \
  GLuint result = glewInit(); \
  ASSERT(result == GLEW_OK);