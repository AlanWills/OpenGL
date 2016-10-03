#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Time/Clock.h"
#include "OpenGL/OpenGLContext.h"
#include "OpenGL/OpenGLWindow.h"

using namespace Engine;

// The amount of time we will allow per update
const GLfloat MS_PER_UPDATE = 1.0f / 60.0f;

int main(int argc, char *argv[])
{ 
  OpenGLContext glContext;
  OpenGLWindow glWindow;
  Game game;

  Clock::init(glfwGetTimerFrequency());
  Clock realtimeClock, gameClock;

  // Initialize game
  game.init(glWindow.getGLWindow());
    
  // DeltaTime variables
  GLfloat elapsedGameTime = 0.0f;
  GLfloat lastFrame = glfwGetTime();
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(glWindow.getGLWindow()))
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

    glfwSwapBuffers(glWindow.getGLWindow());
  }

  return 0;
}