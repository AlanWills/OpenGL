#include "Game.h"
#include "Managers/GameManager.h"
#include "Time/Clock.h"

#include <thread>
#include <chrono>

using namespace Engine;

int main(int argc, char *argv[])
{
  GLFW_INIT();

  GameManager::init();

  GLEW_INIT();

  Clock gameClock;
  Game game;

  // Initialize game
  game.init();

  // DeltaTime variables
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(GameManager::getWindow()->getGLWindow()))
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

    glfwSwapBuffers(GameManager::getWindow()->getGLWindow());
  }

  GLFW_TERMINATE();
  return 0;
}