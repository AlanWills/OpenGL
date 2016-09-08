#include "Shader.h"
#include "Texture.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  // Retrieve the vertex/fragment source code from filePath
  // The ifstream doesn't seem to like GLchar* - maybe I am doing something really silly
  std::string vString, fString;

  if (!readShaderFile(vertexPath.c_str(), vString))
  {
    std::cout << "ERROR::VERTEX::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
  }

  if (!readShaderFile(fragmentPath.c_str(), fString))
  {
    std::cout << "ERROR::FRAGMENT::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
  }

  const GLchar* vertexCode = vString.c_str();
  const GLchar* fragmentCode = fString.c_str();

  // Compile the shaders
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  // Vertex shader
  if (!createAndCompileShader(vertexCode, GL_VERTEX_SHADER, vertex))
  {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Fragment shader
  if (!createAndCompileShader(fragmentCode, GL_FRAGMENT_SHADER, fragment))
  {
    glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Shader program
  m_program = glCreateProgram();
  glAttachShader(m_program, vertex);
  glAttachShader(m_program, fragment);
  glLinkProgram(m_program);

  // Print linking errors (if any)
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // Delete the shaders as they're linked into our program and now no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}


//------------------------------------------------------------------------------------------------
bool Shader::readShaderFile(const GLchar* shaderFilePath, std::string& shaderCode)
{
  std::ifstream shaderFile(shaderFilePath);

  if (!shaderFile.good())
  {
    return false;
  }

  // Read the file into the stream and then close the file handle
  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf();
  shaderFile.close();

  shaderCode = shaderStream.str();
  return true;
}


//------------------------------------------------------------------------------------------------
GLint Shader::createAndCompileShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput)
{
  shaderHandleOutput = glCreateShader(shaderType);
  glShaderSource(shaderHandleOutput, 1, &shaderCode, nullptr);
  glCompileShader(shaderHandleOutput);

  GLint success;
  glGetShaderiv(shaderHandleOutput, GL_COMPILE_STATUS, &success);

  return success;
}


//------------------------------------------------------------------------------------------------
void Shader::useShader()
{
  glUseProgram(m_program);
}


//------------------------------------------------------------------------------------------------
void Shader::bindTexture(int textureMacroNumber, GLuint textureHandle, const std::string& shaderVariableName, int index)
{
  glActiveTexture(textureMacroNumber);
  glBindTexture(GL_TEXTURE_2D, textureHandle);
  glUniform1i(glGetUniformLocation(m_program, shaderVariableName.c_str()), index);
}


//------------------------------------------------------------------------------------------------
void Shader::bindTexture(int textureMacroNumber, Texture texture, const std::string& shaderVariableName, int index)
{
  bindTexture(textureMacroNumber, texture.getTextureHandle(), shaderVariableName, index);
}


//------------------------------------------------------------------------------------------------
void Shader::bindMatrix(const glm::mat4& matrix, const std::string& shaderVariableName)
{
  GLuint matrixLocation = glGetUniformLocation(m_program, shaderVariableName.c_str());
  glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}