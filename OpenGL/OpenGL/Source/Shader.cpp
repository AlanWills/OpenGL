#include "Shader.h"
#include "Texture.h"
#include "Debug.h"

#include <glm/gtc/type_ptr.hpp>
#include <assert.h>
#include <iostream>

//------------------------------------------------------------------------------------------------
Shader::Shader()
{
}

//------------------------------------------------------------------------------------------------
Shader::~Shader()
{
  glDeleteProgram(m_program);
}

//------------------------------------------------------------------------------------------------
void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
  // Compile the shaders
  GLuint vertex, fragment, geometry;

  // Vertex shader
  createShader(vertexSource, GL_VERTEX_SHADER, vertex, "VERTEX");

  // Fragment shader
  createShader(fragmentSource, GL_FRAGMENT_SHADER, fragment, "FRAGMENT");

  // Geometry shader
  if (geometrySource)
  {
    createShader(geometrySource, GL_GEOMETRY_SHADER, geometry, "GEOMETRY");
  }

  // Shader program
  m_program = glCreateProgram();
  glAttachShader(m_program, vertex);
  glAttachShader(m_program, fragment);

  if (geometrySource)
  {
    glAttachShader(m_program, geometry);
  }

  glLinkProgram(m_program);

  // Print linking errors (if any)
  checkCompileErrors(m_program, "PROGRAM");

  // Delete the shaders as they're linked into our program and now no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  if (geometrySource)
  {
    glDeleteShader(geometry);
  }

  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Shader::createShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput, const GLchar* shaderErrorType)
{
  shaderHandleOutput = glCreateShader(shaderType);
  glShaderSource(shaderHandleOutput, 1, &shaderCode, nullptr);
  glCompileShader(shaderHandleOutput);

  checkCompileErrors(shaderHandleOutput, shaderErrorType);
  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Shader::checkCompileErrors(GLuint shaderHandle, const GLchar* shaderErrorType)
{
  GLint success;
  bool isProgram = shaderErrorType == "PROGRAM";

  if (isProgram)
  {
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  }
  else
  {
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
  }

  if (!success)
  {
    GLchar infoLog[1024];

    if (isProgram)
    {
      glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
    }
    else
    {
      glGetShaderInfoLog(shaderHandle, 1024, nullptr, infoLog);
    }

    std::cout << "ERROR::SHADER::" << shaderErrorType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    assert(false);
  }
}

//------------------------------------------------------------------------------------------------
void Shader::use()
{
  glUseProgram(m_program);
  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Shader::setMatrix(const glm::mat4& matrix, const std::string& shaderVariableName) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_program, shaderVariableName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Shader::setVector4(const glm::vec4& vec, const std::string& shaderVariableName) const
{
  glUniform4f(glGetUniformLocation(m_program, shaderVariableName.c_str()), vec.x, vec.y, vec.z, vec.w);
  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Shader::setInt(GLuint inputInt, const std::string& shaderVariableName) const
{
  glUniform1i(glGetUniformLocation(m_program, shaderVariableName.c_str()), inputInt);
  glCheckError();
}