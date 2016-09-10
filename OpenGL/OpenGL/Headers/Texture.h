#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <string>

class Texture
{
public:
  Texture();
  ~Texture();

  void generate(GLuint width, GLuint height, unsigned char* data);
  void bind() const;

  void setInternalFormat(GLuint internalFormat) { m_internalFormat = internalFormat; }
  void setImageFormat(GLuint imageFormat) { m_imageFormat = imageFormat; }

private:
  GLuint m_glTextureHandle;

  int m_width;
  int m_height;

  GLuint m_internalFormat;  // Format of texture object
  GLuint m_imageFormat; // Format of loaded image

  GLuint m_wrap_S; // Wrapping mode on S axis
  GLuint m_wrap_T; // Wrapping mode on T axis
  GLuint m_filter_Min; // Filtering mode if texture pixels < screen pixels
  GLuint m_filter_Max; // Filtering mode if texture pixels > screen pixels
};