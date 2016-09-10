#include "Texture.h"


//------------------------------------------------------------------------------------------------
Texture::Texture()
  : m_glTextureHandle(0),
  m_width(0),
  m_height(0),
  m_internalFormat(GL_RGB),
  m_imageFormat(GL_RGB),
  m_wrap_S(GL_REPEAT),
  m_wrap_T(GL_REPEAT),
  m_filter_Min(GL_LINEAR),
  m_filter_Max(GL_LINEAR)
{
}

//------------------------------------------------------------------------------------------------
Texture::~Texture()
{
  glDeleteTextures(1, &m_glTextureHandle);
}

//------------------------------------------------------------------------------------------------
void Texture::generate(GLuint width, GLuint height, unsigned char* data)
{
  m_width = width;
  m_height = height;

  glBindTexture(GL_TEXTURE_2D, m_glTextureHandle);
  glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);	// Use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes value from next repeat 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_Min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_Max);

  glBindTexture(GL_TEXTURE_2D, 0);
}

//------------------------------------------------------------------------------------------------
void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, m_glTextureHandle);
}