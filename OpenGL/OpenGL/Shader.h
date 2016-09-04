#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include to get all the required OpenGL headers

class Shader
{
public:
  // Constructor reads and builds the shader
  Shader(const std::string& vertexPath, const std::string& fragmentPath);

  // Use the program
  void useShader();

private:
  // Wrapper function for opening the file and reading the contents into the input string
  bool readShaderFile(const GLchar* vertexPath, std::string& shaderCode);

  // Wrapper function for creating a shader with the inputted code and returning a handle
  GLint createAndCompileShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput);

  // The program ID
  GLuint m_program;
};