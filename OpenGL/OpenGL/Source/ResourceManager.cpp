#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::m_textures;
std::map<std::string, Shader>       ResourceManager::m_shaders;


//------------------------------------------------------------------------------------------------
Shader& ResourceManager::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
  m_shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  return m_shaders[name];
}

//------------------------------------------------------------------------------------------------
Shader& ResourceManager::getShader(std::string name)
{
  return m_shaders[name];
}

//------------------------------------------------------------------------------------------------
Texture2D& ResourceManager::loadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
  m_textures[name] = loadTextureFromFile(file, alpha);
  return m_textures[name];
}

//------------------------------------------------------------------------------------------------
Texture2D& ResourceManager::getTexture(std::string name)
{
  return m_textures[name];
}

//------------------------------------------------------------------------------------------------
void ResourceManager::freeResources()
{
  // (Properly) delete all shaders	
  for (auto iter : m_shaders)
  {
    glDeleteProgram(iter.second.ID);
  }

  // (Properly) delete all textures
  for (auto iter : m_textures)
  {
    glDeleteTextures(1, &iter.second.ID);
  }
}

//------------------------------------------------------------------------------------------------
Shader& ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
  // 1. Retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try
  {
    // Open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShaderStream, fShaderStream;
    // Read file's buffer contents into streams
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    // If geometry shader path is present, also load a geometry shader
    if (gShaderFile != nullptr)
    {
      std::ifstream geometryShaderFile(gShaderFile);
      std::stringstream gShaderStream;
      gShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryCode = gShaderStream.str();
    }
  }
  catch (std::exception e)
  {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }
  const GLchar *vShaderCode = vertexCode.c_str();
  const GLchar *fShaderCode = fragmentCode.c_str();
  const GLchar *gShaderCode = geometryCode.c_str();

  // TODO: Add asserts for empty strings

  // 2. Now create shader object from source code
  Shader shader;
  shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
  return shader;
}

//------------------------------------------------------------------------------------------------
Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
  // Create Texture object
  Texture2D texture;
  if (alpha)
  {
    texture.Internal_Format = GL_RGBA;
    texture.Image_Format = GL_RGBA;
  }
  // Load image
  int width, height;
  unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  // Now generate texture
  texture.Generate(width, height, image);
  // And finally free image data
  SOIL_free_image_data(image);
  return texture;
}