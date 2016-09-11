#include "GLHeaders.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Debug.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;

// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

// The amount of time we will allow per update
const GLfloat MS_PER_UPDATE = 1.0f / 60.0f;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();
  glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

  glfwSetKeyCallback(window, key_callback);

  // OpenGL configuration
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glCheckError();

  // Initialize game
  game.init();

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
    game.render(lag / MS_PER_UPDATE);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}

//------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {
      game.setKeyState(key, GL_TRUE);
    }
    else if (action == GLFW_RELEASE)
    {
      game.setKeyState(key, GL_FALSE);
    }
  }
}