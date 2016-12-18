#include "stdafx.h"
#include "Resources/Shader.h"
#include "DebugUtils/Debug.h"
#include "FileSystem/File.h"

#ifdef _DEBUG
#include "OpenGL/TemporaryGLContext.h"
#endif

#include <iostream>


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Shader::Shader()
  {
    // Keep the constructor clear of runtime initialization - if we are using a Pool Allocator it may fail
  }

  //------------------------------------------------------------------------------------------------
  Shader::~Shader()
  {
    if (m_program != 0 && glIsProgram(m_program))
    {
      glDeleteProgram(m_program);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Shader::load(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
  {
    // Retrieve the vertex/fragment/geometry source code from filePath
    std::string vertexCode;
    std::string fragmentCode;

    Kernel::File file(vertexShaderFilePath);
    ASSERT(file.exists());
    file.read(vertexCode);

    file = File(fragmentShaderFilePath);
    ASSERT(file.exists());
    file.read(fragmentCode);

    ASSERT(!vertexCode.empty());
    ASSERT(!fragmentCode.empty());

    // Compile into the graphics card
    compile(vertexCode, fragmentCode);
  }

  //------------------------------------------------------------------------------------------------
  void Shader::compile(const std::string& vertexSource, const std::string& fragmentSource)
  {
    GLuint sVertex, sFragment;

    // Vertex Shader
    createShader(vertexSource, GL_VERTEX_SHADER, sVertex, "VERTEX");
    
    // Fragment Shader
    createShader(fragmentSource, GL_FRAGMENT_SHADER, sFragment, "FRAGMENT");

    // Shader Program
    m_program = glCreateProgram();
    glAttachShader(m_program, sVertex);
    glAttachShader(m_program, sFragment);

    glLinkProgram(m_program);
    checkCompileErrors(m_program, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);

    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::createShader(const std::string& shaderCode, GLenum shaderType, GLuint& shaderHandleOutput, const GLchar* shaderErrorType)
  {
    const char* shaderSource = shaderCode.c_str();

    shaderHandleOutput = glCreateShader(shaderType);
    glShaderSource(shaderHandleOutput, 1, &shaderSource, nullptr);
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
      ASSERT_FAIL();
    }

    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::bind() const
  {
    glUseProgram(m_program);
  }

  //------------------------------------------------------------------------------------------------
  void Shader::unbind() const
  {
    glUseProgram(0);
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setFloat(const GLchar *name, GLfloat value) const
  {
    glUniform1f(glGetUniformLocation(m_program, name), value);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setInteger(const GLchar *name, GLint value) const
  {
    glUniform1i(glGetUniformLocation(m_program, name), value);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y) const
  {
    glUniform2f(glGetUniformLocation(m_program, name), x, y);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector2f(const GLchar *name, const glm::vec2 &value) const
  {
    glUniform2f(glGetUniformLocation(m_program, name), value.x, value.y);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) const
  {
    glUniform3f(glGetUniformLocation(m_program, name), x, y, z);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector3f(const GLchar *name, const glm::vec3 &value) const
  {
    glUniform3f(glGetUniformLocation(m_program, name), value.x, value.y, value.z);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
  {
    glUniform4f(glGetUniformLocation(m_program, name), x, y, z, w);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setVector4f(const GLchar *name, const glm::vec4 &value) const
  {
    glUniform4f(glGetUniformLocation(m_program, name), value.x, value.y, value.z, value.w);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix) const
  {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(matrix));
    glCheckError();
  }
}