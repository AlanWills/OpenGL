#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <SOIL/SOIL.h>

std::unordered_map<std::string, Shader*> ResourceManager::m_shaders;
std::unordered_map<std::string, Texture*> ResourceManager::m_textures;

//------------------------------------------------------------------------------------------------
Shader* ResourceManager::loadShader(const std::string& name, const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
  m_shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  return m_shaders[name];
}

//------------------------------------------------------------------------------------------------
Shader* ResourceManager::getShader(const std::string& name)
{
  return m_shaders[name];
}

//------------------------------------------------------------------------------------------------
Texture* ResourceManager::loadTexture(const GLchar* file, GLboolean alpha, const std::string& name)
{
  std::string fullPath(TEXTURE_DIR);
  fullPath.append(file);

  m_textures[name] = loadTextureFromFile(fullPath.c_str(), alpha);
  return m_textures[name];
}

//------------------------------------------------------------------------------------------------
Texture* ResourceManager::getTexture(const std::string& name)
{
  return m_textures[name];
}

//------------------------------------------------------------------------------------------------
void ResourceManager::freeResources()
{
  // (Properly) delete all shaders	
  for (std::pair<std::string, Shader*> resourcePair : m_shaders)
  {
    // Destructor of Shader calls glDeleteProgram
    delete resourcePair.second;
  }

  // (Properly) delete all textures
  for (auto iter : m_textures)
  {
    // Destructor of Shader calls glDeleteTextures
    delete iter.second;
  }
}

//------------------------------------------------------------------------------------------------
Shader* ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
  // Retrieve the vertex/fragment source code from filePath
  // The ifstream doesn't seem to like GLchar* - maybe I am doing something really silly
  std::string vString, fString, gString;

  std::string fullPath(SHADER_DIR);
  fullPath.append(VERTEX_DIR);
  fullPath.append(vShaderFile);
  if (!readShaderFile(fullPath.c_str(), vString))
  {
  assert(false);
  std::cout << "ERROR::VERTEX::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
  }

  fullPath = SHADER_DIR;
  fullPath.append(FRAGMENT_DIR);
  fullPath.append(fShaderFile);
  if (!readShaderFile(fullPath.c_str(), fString))
  {
  assert(false);
  std::cout << "ERROR::FRAGMENT::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
  }

  if (gShaderFile)
  {
    fullPath = SHADER_DIR;
    fullPath.append(GEOMETRY_DIR);
    fullPath.append(gShaderFile);
    if (!readShaderFile(fullPath.c_str(), gString))
    {
      assert(false);
      std::cout << "ERROR::GEOMETRY::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
    }
  }

  const GLchar* vertexCode = vString.c_str();
  const GLchar* fragmentCode = fString.c_str();
  const GLchar* geometryCode = gShaderFile != nullptr ? gString.c_str() : nullptr;

  Shader* shader = new Shader();
  shader->compile(vertexCode, fragmentCode, geometryCode);

  return shader;
}

//------------------------------------------------------------------------------------------------
bool ResourceManager::readShaderFile(const GLchar* shaderFilePath, std::string& shaderCodeOutput)
{
  std::ifstream shaderFile(shaderFilePath);

  if (!shaderFile.good())
  {
    assert(false);
    return false;
  }

  // Read the file into the stream and then close the file handle
  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf();
  shaderFile.close();

  shaderCodeOutput = shaderStream.str();
  return true;
}

//------------------------------------------------------------------------------------------------
Texture* ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha)
{
  Texture* texture = new Texture();
  if (alpha)
  {
    texture->setImageFormat(GL_RGBA);
    texture->setInternalFormat(GL_RGBA);
  }

  // Load image
  int width, height;
  unsigned char* image = SOIL_load_image(file, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

  // Now generate texture
  texture->generate(width, height, image);

  // And finally free image data
  SOIL_free_image_data(image);

  return texture;
}