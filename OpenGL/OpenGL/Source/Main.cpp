#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Time/Clock.h"
#include "OpenGL/OpenGLWindow.h"

using namespace Engine;

// The amount of time we will allow per update
const GLfloat MS_PER_UPDATE = 1.0f / 60.0f;

int main(int argc, char *argv[])
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  OpenGLWindow glWindow;
  GLFWwindow* window = glWindow.getGLWindow();

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  Game game;

  Clock::init(glfwGetTimerFrequency());
  Clock realtimeClock, gameClock;

  // Initialize game
  game.init(window);
    
  // DeltaTime variables
  GLfloat elapsedGameTime = 0.0f;
  GLfloat lastFrame = glfwGetTime();
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(window))
  {
    // Calculate delta time
    GLfloat currentFrame = glfwGetTime();
    elapsedGameTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    lag += elapsedGameTime;

    glfwPollEvents();

    // Manage user input
    game.handleInput(elapsedGameTime);

    // Update Game state
    // We use a variable render fixed update loop
    while (lag >= MS_PER_UPDATE)
    {
      game.update(elapsedGameTime);
      lag -= MS_PER_UPDATE;
    }

    // Render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    game.render(elapsedGameTime, lag / MS_PER_UPDATE);

    glfwSwapBuffers(window);
  }

  return 0;
}