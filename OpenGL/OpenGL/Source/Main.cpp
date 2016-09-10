#include "GLHeaders.h"

#include "Game.h"
#include "ResourceManager.h"

#define MS_PER_UPDATE 16.66666666

// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
  // Set some GL constants
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GL window
  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Tell the current thread it is associated with this window
  glfwMakeContextCurrent(window);

  // Initialize glew before we start calling any OpenGL functions
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Set up the key callback for keyboard input
  glfwSetKeyCallback(window, keyCallback);

  // Set the size of the rendering window
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Time step
  GLfloat lastFrame = glfwGetTime(), lag = 0.0f;

  // Fixed time step and variable render game loop which keeps the window open
  while (!glfwWindowShouldClose(window))
  {
    GLfloat currentFrame = glfwGetTime();
    GLfloat elapsed = currentFrame - lastFrame;
    lastFrame = currentFrame;
    lag += elapsed;

    // Check and call events
    glfwPollEvents();

    // Process input
    game.handleInput(elapsed);

    while (lag >= MS_PER_UPDATE)
    {
      // Update
      game.update(elapsed);
      lag -= MS_PER_UPDATE;
    }

    // Clear the buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render using lag / MS_PER_UPDATE so that we can make up for render being out of step with update in variable render game loop
    game.draw(lag / MS_PER_UPDATE);

    // Swap the buffers
    glfwSwapBuffers(window);
  }

  // Clear up all resources
  ResourceManager::freeResources();

  // Clean up resources
  glfwTerminate();
	return 0;
}

//------------------------------------------------------------------------------------------------
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true
  // closing the application

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {
      game.setKey(key, true);
    }
    else if (action == GLFW_RELEASE)
    {
      game.setKey(key, false);
    }
  }
}

//------------------------------------------------------------------------------------------------
//void mouseCallback(GLFWwindow* window, double xPos, double yPos)
//{
//  if (firstMouse)
//  {
//    lastX = xPos;
//    lastY = yPos;
//    firstMouse = false;
//  }
//
//  GLfloat xOffset = xPos - lastX;
//  GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
//
//  lastX = xPos;
//  lastY = yPos;
//
//  Camera::getInstance().processMouseMovement(xOffset, yOffset);
//}
//
////------------------------------------------------------------------------------------------------
//void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
//{
//  Camera::getInstance().zoom(yOffset);
//}

//------------------------------------------------------------------------------------------------
//void doMovement(GLfloat deltaTime)
//{
//  if (keys[GLFW_KEY_W])
//  {
//    Camera::getInstance().move(CameraMovement::kForward, deltaTime);
//  }
//  if (keys[GLFW_KEY_S])
//  {
//    Camera::getInstance().move(CameraMovement::kBackward, deltaTime);
//  }
//  if (keys[GLFW_KEY_A])
//  {
//    Camera::getInstance().move(CameraMovement::kLeft, deltaTime);
//  }
//  if (keys[GLFW_KEY_D])
//  {
//    Camera::getInstance().move(CameraMovement::kRight, deltaTime);
//  }
//}