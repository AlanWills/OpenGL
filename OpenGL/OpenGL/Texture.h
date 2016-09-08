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
  Texture(const std::string& textureAsset);
  ~Texture();

  GLuint getTextureHandle() const { return m_glTextureHandle; }

private:
  GLuint m_glTextureHandle;
  int m_width;
  int m_height;
};

