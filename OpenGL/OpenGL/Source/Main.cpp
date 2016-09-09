#include <SOIL\SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "GLHeaders.h"
#include "Shaders/Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Cube.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Input
bool keys[1024];

// Time step
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Camera
Camera camera;
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void doMovement();

int main()
{
  // Set some GL constants
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GL window
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
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

  // Set the size of the rendering window
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Set up the key callback for keyboard input
  glfwSetKeyCallback(window, keyCallback);

  // Set up the mouse input callback
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);

  // Set the clear colour
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  // Create our shader
  Shader shader("experiment.vs", "experiment.frag");

  // Cube positions
  glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  // Cube object which holds gl data
  // We can use this one object to draw multiple instances
  Cube cube;

  std::string directoryPath = "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\Assets";
  Texture containerTexture(directoryPath + "container.jpg");
  Texture faceTexture(directoryPath + "awesomeface.png");

  // Draw in wireframe
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Game loop to keep the window open
  while (!glfwWindowShouldClose(window))
  {
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Check and call events
    glfwPollEvents();
    doMovement();

    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera matrices
    glm::mat4 projection, view;
    camera.getProjectionMatrix(WIDTH, HEIGHT, projection);
    camera.getViewMatrix(view);

    // Ready gl to use this shader and bind the view and projection matrices to the uniform shader variables
    shader.useShader(view, projection);
    GLuint shaderProgram = shader.getProgram();

    // Bind the textures to the shader samplers
    shader.bindUniformTexture(GL_TEXTURE0, containerTexture, "ourTexture", 0);
    shader.bindUniformTexture(GL_TEXTURE1, faceTexture, "ourTexture2", 1);

    cube.beginDraw();
    for (GLuint i = 0; i < 10; i++)
    {
      glm::mat4 model;
      model = glm::translate(model, cubePositions[i]);
      GLfloat angle = glm::radians(20.0f * i);
      model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

      cube.drawInstance(shader, model);
    }
    cube.endDraw();

    // Swap the buffers
    glfwSwapBuffers(window);
  }

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

  if (action == GLFW_PRESS)
  {
    keys[key] = true;
  }
  else if (action == GLFW_RELEASE)
  {
    keys[key] = false;
  }
}

//------------------------------------------------------------------------------------------------
void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
  if (firstMouse)
  {
    lastX = xPos;
    lastY = yPos;
    firstMouse = false;
  }

  GLfloat xOffset = xPos - lastX;
  GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

  lastX = xPos;
  lastY = yPos;

  camera.processMouseMovement(xOffset, yOffset);
}

//------------------------------------------------------------------------------------------------
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
  camera.zoom(yOffset);
}

//------------------------------------------------------------------------------------------------
void doMovement()
{
  if (keys[GLFW_KEY_W])
  {
    camera.move(CameraMovement::kForward, deltaTime);
  }
  if (keys[GLFW_KEY_S])
  {
    camera.move(CameraMovement::kBackward, deltaTime);
  }
  if (keys[GLFW_KEY_A])
  {
    camera.move(CameraMovement::kLeft, deltaTime);
  }
  if (keys[GLFW_KEY_D])
  {
    camera.move(CameraMovement::kRight, deltaTime);
  }
}