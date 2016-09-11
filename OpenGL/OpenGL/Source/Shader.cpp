#include "Shader.h"
#include "Debug.h"

#include <iostream>

//------------------------------------------------------------------------------------------------
Shader::Shader()
{
}

//------------------------------------------------------------------------------------------------
void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
  GLuint sVertex, sFragment, gShader;
  // Vertex Shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");
  // Fragment Shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");
  // If geometry shader source code is given, also compile geometry shader
  if (geometrySource != nullptr)
  {
    gShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gShader, 1, &geometrySource, NULL);
    glCompileShader(gShader);
    checkCompileErrors(gShader, "GEOMETRY");
  }
  // Shader Program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, sVertex);
  glAttachShader(this->ID, sFragment);
  if (geometrySource != nullptr)
    glAttachShader(this->ID, gShader);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");
  // Delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
  if (geometrySource != nullptr)
    glDeleteShader(gShader);
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
  glUseProgram(this->ID);
}

void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}