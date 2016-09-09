#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include to get all the required OpenGL headers
#include <glm/gtc/matrix_transform.hpp>

class Texture;

#define VERTEX_DIR "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\Shaders\\Vertex\\"
#define FRAGMENT_DIR "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\Shaders\\Fragment\\"

// Shader variable names
#define MODEL_MATRIX "model"
#define VIEW_MATRIX "view"
#define PROJECTION_MATRIX "projection"
#define COLOUR "objectColour"

class Shader
{
public:
  // Constructor reads and builds the shader
  Shader(const std::string& vertexPath, const std::string& fragmentPath);

  const GLuint getProgram() { return m_program; }

  // Use the program
  void useShader(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

  /// \brief Used to bind textures to uniform sampler variables in the shader
  void bindUniformTexture(int textureMacroNumber, GLuint textureHandle, const std::string& shaderVariableName, int index);
  void bindUniformTexture(int textureMacroNumber, Texture texture, const std::string& shaderVariableName, int index);

  /// brief Used to bind matrices to uniform sampler variables in the shader
  void bindUniformMatrix(const glm::mat4& matrix, const std::string& shaderVariableName);

private:
  // Wrapper function for opening the file and reading the contents into the input string
  bool readShaderFile(const GLchar* vertexPath, std::string& shaderCode);

  // Wrapper function for creating a shader with the inputted code and returning a handle
  GLint createAndCompileShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput);

  // The program ID
  GLuint m_program;
};