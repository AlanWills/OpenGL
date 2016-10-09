#include "GLHeaders.h"
#include "Game.h"
#include "Debugging/DebugManager.h"
#include "Input/InputManager.h"
#include "Resources/ResourceManager.h"
#include "Time/Clock.h"
#include "OpenGL/OpenGLWindow.h"

#include <thread>
#include <chrono>

using namespace Engine;

int main(int argc, char *argv[])
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // TODO: Move to screen manager class
  OpenGLWindow glWindow;
  GLFWwindow* window = glWindow.getGLWindow();

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  DebugManager::init();
  InputManager::init(window);
  ResourceManager::init();
  Clock::init();

  Clock gameClock;
  Game game;

  // Initialize game
  game.init(window);

  // DeltaTime variables
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(window))
  {
    gameClock.update();

    GLfloat elapsedGameTime = gameClock.getElapsedDeltaTime();
    lag += elapsedGameTime;

    GLfloat gameSecondsPerUpdate = gameClock.getTimeScale() / gameClock.getTargetFramesPerSecond();

    glfwPollEvents();

    // Manage user input
    game.handleInput(elapsedGameTime);
    
    // Update Game state
    // We use a variable render fixed update loop
    while (lag >= gameSecondsPerUpdate)
    {
      game.update(gameSecondsPerUpdate);
      lag -= gameSecondsPerUpdate;
    }

    // Render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    game.render(lag);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}