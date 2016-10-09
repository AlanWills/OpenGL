#include "stdafx.h"
#include "Resources/ResourceManager.h"

#include <SOIL/SOIL.h>

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  // Instantiate static variables
  TextureMap   ResourceManager::m_textures;
  ShaderMap    ResourceManager::m_shaders;


  //------------------------------------------------------------------------------------------------
  void ResourceManager::init()
  {
    glewExperimental = GL_TRUE;
    glewInit();
  }

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
    // 1. Retrieve the vertex/fragment/geometry source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    Path path(DIRECTORY);
    path.combine(SHADER_DIR).combine(VERTEX_SHADER_DIR).combine(vShaderFile);

    File file(path);
    file.read(vertexCode);

    path = Path(DIRECTORY);
    path.combine(SHADER_DIR).combine(FRAGMENT_SHADER_DIR).combine(fShaderFile);

    file = File(path);
    file.read(fragmentCode);

    if (gShaderFile)
    {
      path = Path(DIRECTORY);
      path.combine(SHADER_DIR).combine(GEOMETRY_SHADER_DIR).combine(gShaderFile);

      file = File(path);
      file.read(geometryCode);
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
    Path path(DIRECTORY);
    path.combine(TEXTURE_DIR).combine(file);

    int width, height;
    unsigned char* image = SOIL_load_image(path.asString().c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    assert(image);

    // Now generate texture
    texture->generate(width, height, image);

    // And finally free image data
    SOIL_free_image_data(image);
    return texture;
  }
}