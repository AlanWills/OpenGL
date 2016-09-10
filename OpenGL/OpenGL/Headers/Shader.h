#pragma once

#include <string>

#include <GL/glew.h> // Include to get all the required OpenGL headers
#include <glm/gtc/matrix_transform.hpp>

class Texture;

// Shader variable names
#define MODEL_MATRIX "model"
#define VIEW_MATRIX "view"
#define PROJECTION_MATRIX "projection"
#define TEXTURE "objectTexture"
#define COLOUR "objectColour"

class Shader
{
public:
  // Constructor reads and builds the shader
  Shader();
  ~Shader();

  void compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

  // Use the program
  void use();

  /// brief Used to bind matrices to uniform sampler variables in the shader
  void setMatrix(const glm::mat4& matrix, const std::string& shaderVariableName) const;

  /// \brief Used to bind vector4s to uniform sampler variables in the shader
  void setVector4(const glm::vec4& vec, const std::string& shaderVariableName) const;

  /// \brief Used to bind ints to uniform sampler variables in the shader 
  void setInt(GLuint inputInt, const std::string& shaderVariableName) const;

private:
  // Wrapper function for creating a shader with the inputted code and returning a handle
  void createShader(const GLchar* shaderCode, GLenum shaderType, GLuint& shaderHandleOutput, const GLchar* shaderErrorType);

  void checkCompileErrors(GLuint shaderHandle, const GLchar* shaderErrorType);

  // The program ID
  GLuint m_program;
};