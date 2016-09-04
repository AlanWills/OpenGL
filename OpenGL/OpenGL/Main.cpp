#include "Main.h"
#include "Shader.h"
#include <SOIL\SOIL.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true
  // closing the application

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

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

  // Set up the key callback for quitting the application
  glfwSetKeyCallback(window, key_callback);

  // Set the clear colour
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Create our shader
  std::string folderPath("C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\");
  Shader shader(folderPath + "simple.vs", folderPath + "simple.frag");

  // Store all of this state data in one object for easy reuse
  GLfloat vertices[] = 
  {
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // Top Right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top Left 
  };

  // Order in which we draw the triangles
  GLuint indices[] = 
  {  
    // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
  };

  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);

  int texWidth, texHeight;
  std::string directoryPath = "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\";
  unsigned char* image = SOIL_load_image((directoryPath + "container.jpg").c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);

  // Binding = give GL a GLuint for some kind of object type (like texture).
  // Then do some operations on the object type.
  // It associates these settings/data with this int
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Cleanup
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  image = SOIL_load_image((directoryPath + "awesomeface.png").c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);

  GLuint texture2;
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Cleanup
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Draw in wireframe
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Game loop to keep the window open
  while (!glfwWindowShouldClose(window))
  {
    // Check and call events
    glfwPollEvents();

    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    shader.useShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Unbind so we don't accidently reconfigure

    // Swap the buffers
    glfwSwapBuffers(window);
  }

  // Clean up resources
  glfwTerminate();
	return 0;
}