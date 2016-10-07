#include "Resources/ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

// Instantiate static variables
TextureMap   ResourceManager::m_textures;
ShaderMap    ResourceManager::m_shaders;


//------------------------------------------------------------------------------------------------
Shader* ResourceManager::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, const std::string& name)
{
  Shader* shader = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  m_shaders[name] = std::unique_ptr<Shader>(shader);
  return shader;
}

//------------------------------------------------------------------------------------------------
Shader* ResourceManager::getShader(const std::string& name)
{
  return m_shaders[name].get();
}

//------------------------------------------------------------------------------------------------
Texture2D* ResourceManager::loadTexture(const GLchar *file, GLboolean alpha, const std::string& name)
{
  Texture2D* texture = loadTextureFromFile(file, alpha);
  m_textures[name] = std::unique_ptr<Texture2D>(texture);
  return texture;
}

//------------------------------------------------------------------------------------------------
Texture2D* ResourceManager::getTexture(const std::string& name)
{
  return m_textures[name].get();
}

//------------------------------------------------------------------------------------------------
Shader* ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
  // 1. Retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;

  std::string fullPath(DIRECTORY);
  fullPath.append(SHADER_DIR);
  fullPath.append(VERTEX_SHADER_DIR);
  fullPath.append(vShaderFile);
  readFile(fullPath.c_str(), vertexCode);

  fullPath = DIRECTORY;
  fullPath.append(SHADER_DIR);
  fullPath.append(FRAGMENT_SHADER_DIR);
  fullPath.append(fShaderFile);
  readFile(fullPath.c_str(), fragmentCode);

  if (gShaderFile)
  {
    fullPath = DIRECTORY;
    fullPath.append(SHADER_DIR);
    fullPath.append(GEOMETRY_SHADER_DIR);
    fullPath.append(gShaderFile);
    readFile(fullPath.c_str(), geometryCode);
  }

  assert(!vertexCode.empty());
  assert(!fragmentCode.empty());
  assert(!gShaderFile || !geometryCode.empty());

  const GLchar *vShaderCode = vertexCode.c_str();
  const GLchar *fShaderCode = fragmentCode.c_str();
  const GLchar *gShaderCode = geometryCode.c_str();

  // 2. Now create shader object from source code
  Shader* shader = new Shader();
  shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

  return shader;
}

//------------------------------------------------------------------------------------------------
void ResourceManager::readFile(const GLchar* filePath, std::string& outputFileText)
{
  std::ifstream file(filePath);
  std::stringstream stream;

  if (file.bad())
  {
    std::cout << "ERROR::Failed to read file" << filePath << std::endl;
    return;
  }

  stream << file.rdbuf();
  file.close();

  outputFileText = stream.str();
}

//------------------------------------------------------------------------------------------------
Texture2D* ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha)
{
  // Create Texture object
  Texture2D* texture = new Texture2D();
  if (alpha)
  {
    texture->setInternalFormat(GL_RGBA);
    texture->setImageFormat(GL_RGBA);
  }

  // Load image
  std::string fullPath(DIRECTORY);
  fullPath.append(TEXTURE_DIR);
  fullPath.append(file);

  int width, height;
  unsigned char* image = SOIL_load_image(fullPath.c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  assert(image);

  // Now generate texture
  texture->generate(width, height, image);

  // And finally free image data
  SOIL_free_image_data(image);
  return texture;
}