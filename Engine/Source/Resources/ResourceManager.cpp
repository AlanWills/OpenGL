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

  const Path            ResourceManager::m_resourceDirectoryPath(Directory::getExecutingAppDirectory(), DIRECTORY);
  const Path            ResourceManager::m_textureDirectoryPath(m_resourceDirectoryPath.asString(), TEXTURE_DIR);
  const Path            ResourceManager::m_shaderDirectoryPath(m_resourceDirectoryPath.asString(), SHADER_DIR);
  const Path            ResourceManager::m_vertexShaderDirectoryPath(m_resourceDirectoryPath.asString(), VERTEX_SHADER_DIR);
  const Path            ResourceManager::m_fragmentShaderDirectoryPath(m_resourceDirectoryPath.asString(), FRAGMENT_SHADER_DIR);
  const Path            ResourceManager::m_geometryShaderDirectoryPath(m_resourceDirectoryPath.asString(), GEOMETRY_SHADER_DIR);


  //------------------------------------------------------------------------------------------------
  void ResourceManager::init()
  {
    glewExperimental = GL_TRUE;
    glewInit();
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShader(
    const std::string& vShaderRelativeFilePath,
    const std::string& fShaderRelativeFilePath,
    const std::string& gShaderRelativeFilePath,
    StringId name)
  {
    Path vertexShader(m_vertexShaderDirectoryPath), fragmentShader(m_fragmentShaderDirectoryPath), geometryShader(m_geometryShaderDirectoryPath);
    vertexShader.combine(vShaderRelativeFilePath);
    fragmentShader.combine(fShaderRelativeFilePath);
    geometryShader.combine(gShaderRelativeFilePath);

    Shader* shader = loadShaderFromFile(vertexShader.asString(), fragmentShader.asString(), geometryShader.asString());
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
    Path fullPath(m_textureDirectoryPath);
    fullPath.combine(relativeFilePath);

    Texture2D* texture = loadTextureFromFile(fullPath.asString(), alpha);
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
  Shader* ResourceManager::loadShaderFromFile(
    const std::string& vShaderRelativeFilePath,
    const std::string& fShaderRelativeFilePath,
    const std::string& gShaderRelativeFilePath)
  {
    // Create shader object
    Shader* shader = nullptr;
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

    ASSERT(shader);

    // Retrieve the vertex/fragment/geometry source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    File file(vShaderRelativeFilePath);
    ASSERT(file.exists());
    file.read(vertexCode);

    file = File(fShaderRelativeFilePath);
    ASSERT(file.exists());
    file.read(fragmentCode);

    if (!gShaderRelativeFilePath.empty())
    {
      file = File(gShaderRelativeFilePath);
      ASSERT(file.exists());
      file.read(geometryCode);
    }

    ASSERT(!vertexCode.empty());
    ASSERT(!fragmentCode.empty());
    ASSERT(gShaderRelativeFilePath.empty() || !geometryCode.empty());

    // Compile into the graphics card
    shader->compile(vertexCode, fragmentCode, !gShaderRelativeFilePath.empty() ? geometryCode : "");

    return shader;
  }

  //------------------------------------------------------------------------------------------------
  Texture2D* ResourceManager::loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha)
  {
    // Create Texture object
    Texture2D* texture = nullptr;
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

    ASSERT(texture);

    if (alpha)
    {
      texture->setInternalFormat(GL_RGBA);
      texture->setImageFormat(GL_RGBA);
    }

#ifdef _DEBUG
    // Do some debug checking on the image path to make sure it exists
    File file(fullFilePath);
    ASSERT(file.exists());
#endif

    // Load the image

    int width, height;
    unsigned char* image = SOIL_load_image(fullFilePath.c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    ASSERT(image);

    // Now generate texture
    texture->generate(width, height, image);

    // And finally free image data
    SOIL_free_image_data(image);
    return texture;
  }
}