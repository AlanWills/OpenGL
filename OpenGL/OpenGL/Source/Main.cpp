#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "Time/Clock.h"


// The Width of the screen
const GLuint SCREEN_WIDTH = 800;

// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

// The amount of time we will allow per update
const GLfloat MS_PER_UPDATE = 1.0f / 60.0f;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

using namespace Engine;

int main(int argc, char *argv[])
{ 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  Clock::init(glfwGetTimerFrequency());
  Clock realtimeClock, gameClock;

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  // OpenGL configuration
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glCheckError();

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

  glfwTerminate();
  return 0;
}