#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
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

  OpenGLWindow glWindow;
  GLFWwindow* window = glWindow.getGLWindow();

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  Game game;

  Clock::init();

  // Initialize game
  game.init(window);
    
  Clock realtimeClock, gameClock;
  //gameClock.setTimeScale(0.1f);

  // DeltaTime variables
  GLfloat current = glfwGetTime(), previous = 0;
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(window))
  {
    previous = current;
    current = glfwGetTime();

    GLfloat elapsedGameTime = (current - previous) * gameClock.getTimeScale();
    lag += elapsedGameTime;

    GLfloat gameSecondsPerUpdate = gameClock.getTimeScale() / gameClock.getTargetFramesPerSecond();

    realtimeClock.update(current - previous);
    gameClock.update(elapsedGameTime);

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
    game.render(elapsedGameTime, lag / gameSecondsPerUpdate);

    glfwSwapBuffers(window);

    GLfloat elapsed = glfwGetTime() - current;
    if (elapsed < (1.0f / gameClock.getTargetFramesPerSecond()))
    {
      std::this_thread::sleep_for(std::chrono::milliseconds((long)(elapsed * 1000)));
    }
  }

  glfwTerminate();
  return 0;
}