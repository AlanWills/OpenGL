#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Time/Clock.h"
#include "OpenGL/OpenGLWindow.h"

using namespace Engine;

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

  Clock::init();

  // Initialize game
  game.init(window);
    
  // DeltaTime variables
  GLfloat elapsedGameTime = 0.0f;
  GLfloat lag = 0.0f;

  Clock realtimeClock, gameClock;
  gameClock.setTimeScale(0.05f);

  while (!glfwWindowShouldClose(window))
  {
    // We have a problem - the longer the catch up loop takes the longer the next frame delta will be because glfwTimer runs separately to our game
    // We will need to pause the gameClock or something during this loop

    // Single step for now cos weird stuff is happening with timers
    realtimeClock.singleStep();
    gameClock.singleStep();

    // Calculate delta time
    elapsedGameTime = gameClock.getElapsedDeltaTime();
    lag += elapsedGameTime;

    glfwPollEvents();

    // Manage user input
    game.handleInput(elapsedGameTime);
    
    // Update Game state
    // We use a variable render fixed update loop
    // while (lag >= S_PER_UPDATE * gameClock.getTimeScale())
    {
      game.update(elapsedGameTime);
      //lag -= S_PER_UPDATE;
    }

    // Render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    game.render(elapsedGameTime, 0 /*lag / (S_PER_UPDATE * gameClock.getTimeScale())*/);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}