#include "stdafx.h"
#include "Resources/ResourceManager.h"

#include <SOIL/SOIL.h>

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  // Instantiate static variables
  ShaderMap             ResourceManager::m_shaders;
  TextureMap            ResourceManager::m_textures;

  ShaderPool            ResourceManager::m_shaderPool;
  TexturePool           ResourceManager::m_texturePool;

  ShaderPoolOverflow    ResourceManager::m_shaderOverflow;
  TexturePoolOverflow   ResourceManager::m_textureOverflow;


  //------------------------------------------------------------------------------------------------
  void ResourceManager::init()
  {
    glewExperimental = GL_TRUE;
    glewInit();
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, StringId name)
  {
    Shader* shader = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    m_shaders[name] = shader;
    return shader;
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::getShader(StringId name)
  {
    if (m_shaders.find(name) == m_shaders.end())
    {
      ASSERT_FAIL_MSG("Shader file does not exist");

      /// TODO: Return a default shader or something?
      return nullptr;
    }

    return m_shaders[name];
  }

  //------------------------------------------------------------------------------------------------
  Texture2D* ResourceManager::loadTexture(const std::string& relativeFilePath, GLboolean alpha, StringId name)
  {
    Path path(DIRECTORY, TEXTURE_DIR);
    path.combine(relativeFilePath);

    Texture2D* texture = loadTextureFromFile(path.asString(), alpha);
    m_textures[name] = texture;
    return texture;
  }

  //------------------------------------------------------------------------------------------------
  Texture2D* ResourceManager::getTexture(StringId name)
  {
    if (m_textures.find(name) == m_textures.end())
    {
      ASSERT_FAIL_MSG("Texture does not exist");

      /// TODO: Return a default texture or something?
      return nullptr;
    }

    return m_textures[name];
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
  {
    // Create shader object
    Shader* shader;
    if (m_shaderPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      shader = m_shaderPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new shader and then store it in the overflow vector
      shader = new Shader();
      m_shaderOverflow.push_back(std::unique_ptr<Shader>(shader));
    }

    // Retrieve the vertex/fragment/geometry source code from filePath
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

    // Compile into the graphics card
    shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
  }

  //------------------------------------------------------------------------------------------------
  Texture2D* ResourceManager::loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha)
  {
    // Create Texture object
    Texture2D* texture;
    if (m_texturePool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      texture = m_texturePool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new texture and then store it in the overflow vector
      texture = new Texture2D();
      m_textureOverflow.push_back(std::unique_ptr<Texture2D>(texture));
    }

    if (alpha)
    {
      texture->setInternalFormat(GL_RGBA);
      texture->setImageFormat(GL_RGBA);
    }

    // Load image
    Path path(DIRECTORY);
    path.combine(TEXTURE_DIR).combine(fullFilePath);

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