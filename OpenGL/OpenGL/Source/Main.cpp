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

  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  GLuint m_width = mode->width;
  GLuint m_height = mode->height;

  GLFWwindow* m_window = glfwCreateWindow(m_width, m_height, "Breakout", nullptr, nullptr);
  glfwMakeContextCurrent(m_window);

  // OpenGL configuration
  glViewport(0, 0, m_width, m_height);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  //OpenGLWindow glWindow;
  Game game;

  Clock::init(glfwGetTimerFrequency());
  Clock realtimeClock, gameClock;

  // Initialize game
  game.init(m_window);
    
  // DeltaTime variables
  GLfloat elapsedGameTime = 0.0f;
  GLfloat lastFrame = glfwGetTime();
  GLfloat lag = 0.0f;

  while (!glfwWindowShouldClose(m_window))
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

    glfwSwapBuffers(m_window);
  }

  return 0;
}