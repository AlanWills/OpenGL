#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

class Main
{

private:
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};