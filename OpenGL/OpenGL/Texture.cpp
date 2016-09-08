#include "Texture.h"

#include <SOIL\SOIL.h>


//------------------------------------------------------------------------------------------------
Texture::Texture(const std::string& textureAsset)
  : m_glTextureHandle(0),
    m_width(0),
    m_height(0)
{
  std::string directoryPath = "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\";
  unsigned char* image = SOIL_load_image(textureAsset.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGB);

  glGenTextures(1, &m_glTextureHandle);
  glBindTexture(GL_TEXTURE_2D, m_glTextureHandle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Cleanup
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
}


//------------------------------------------------------------------------------------------------
Texture::~Texture()
{
}
