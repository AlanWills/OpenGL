#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
  // State
  GLuint ID;

  // Constructor reads and builds the shader
  Shader();
  ~Shader();
  
  // Note: geometry source code is optional
  // Compiles the shader from given source code
  void compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

  // Sets the current shader as active
  void use() const;

  // Utility functions
  void setFloat(const GLchar *name, GLfloat value) const;
  void setInteger(const GLchar *name, GLint value) const;
  void setVector2f(const GLchar *name, GLfloat x, GLfloat y) const;
  void setVector2f(const GLchar *name, const glm::vec2 &value) const;
  void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) const;
  void setVector3f(const GLchar *name, const glm::vec3 &value) const;
  void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
  void setVector4f(const GLchar *name, const glm::vec4 &value) const;
  void setMatrix4(const GLchar *name, const glm::mat4 &matrix) const;

private:
  // Wrapper function for creating a shader with the inputted code and returning a handle
  void createShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput, const GLchar* shaderErrorType);
  
  void checkCompileErrors(GLuint shaderHandle, const GLchar* shaderErrorType);
  
  // The program ID
  GLuint m_program;
};