#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include to get all the required OpenGL headers
#include <glm/gtc/matrix_transform.hpp>

class Texture;

// Shader variable names
#define MODEL_MATRIX "model"
#define VIEW_MATRIX "view"
#define PROJECTION_MATRIX "projection"
#define COLOUR "inputColour"

class Shader
{
public:
  // Constructor reads and builds the shader
  Shader(const std::string& vertexPath, const std::string& fragmentPath);

  const GLuint getProgram() { return m_program; }

  // Use the program
  void useShader();

  /// \brief Used to bind textures to uniform sampler variables in the shader
  void bindTexture(int textureMacroNumber, GLuint textureHandle, const std::string& shaderVariableName, int index);
  void bindTexture(int textureMacroNumber, Texture texture, const std::string& shaderVariableName, int index);

  void bindMatrix(const glm::mat4& matrix, const std::string& shaderVariableName);

private:
  // Wrapper function for opening the file and reading the contents into the input string
  bool readShaderFile(const GLchar* vertexPath, std::string& shaderCode);

  // Wrapper function for creating a shader with the inputted code and returning a handle
  GLint createAndCompileShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput);

  // The program ID
  GLuint m_program;
};