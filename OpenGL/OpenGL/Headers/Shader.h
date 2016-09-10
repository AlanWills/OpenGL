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
#define COLOUR "objectColour"

class Shader
{
public:
  // Constructor reads and builds the shader
  Shader();
  ~Shader();

  void compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

  // Use the program
  Shader& use();

  /// brief Used to bind matrices to uniform sampler variables in the shader
  void setMatrix(const glm::mat4& matrix, const std::string& shaderVariableName);

private:
  // Wrapper function for opening the file and reading the contents into the input string
  bool readShaderFile(const GLchar* vertexPath, std::string& shaderCode);

  // Wrapper function for creating a shader with the inputted code and returning a handle
  void createShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput, const GLchar* shaderErrorType);

  void checkCompileErrors(GLuint shaderHandle, const GLchar* shaderErrorType);

  // The program ID
  GLuint m_program;
};