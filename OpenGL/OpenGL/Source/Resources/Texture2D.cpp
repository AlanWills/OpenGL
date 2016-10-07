#include <iostream>

#include "Resources/Texture2D.h"


//------------------------------------------------------------------------------------------------
Texture2D::Texture2D()
: m_textureHandle(0),
  m_width(0), 
  m_height(0), 
  m_internalFormat(GL_RGB), 
  m_imageFormat(GL_RGB), 
  m_wrap_S(GL_REPEAT), 
  m_wrap_T(GL_REPEAT), 
  m_filter_Min(GL_LINEAR), 
  m_filter_Max(GL_LINEAR)
{
  glGenTextures(1, &m_textureHandle);
}

//------------------------------------------------------------------------------------------------
Texture2D::~Texture2D()
{
  glDeleteTextures(1, &m_textureHandle);
}

//------------------------------------------------------------------------------------------------
void Texture2D::generate(GLuint width, GLuint height, unsigned char* data)
{
  m_width = width;
  m_height = height;

  // Create Texture
  glBindTexture(GL_TEXTURE_2D, m_textureHandle);
  glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

  // Set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_Min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_Max);

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

//------------------------------------------------------------------------------------------------
void Texture2D::bind() const
{
  glBindTexture(GL_TEXTURE_2D, m_textureHandle);
}