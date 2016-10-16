#include "stdafx.h"
#include "Resources/ResourceManager.h"
#include "OpenGL/OpenGLWindow.h"

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

  Path                  ResourceManager::m_resourceDirectoryPath(Directory::getExecutingAppDirectory(), DIRECTORY);
  Path                  ResourceManager::m_textureDirectoryPath(m_resourceDirectoryPath.asString(), TEXTURE_DIR);
  Path                  ResourceManager::m_shaderDirectoryPath(m_resourceDirectoryPath.asString(), SHADER_DIR);
  Path                  ResourceManager::m_vertexShaderDirectoryPath(m_shaderDirectoryPath.asString(), VERTEX_SHADER_DIR);
  Path                  ResourceManager::m_fragmentShaderDirectoryPath(m_shaderDirectoryPath.asString(), FRAGMENT_SHADER_DIR);
  Path                  ResourceManager::m_geometryShaderDirectoryPath(m_shaderDirectoryPath.asString(), GEOMETRY_SHADER_DIR);


  //------------------------------------------------------------------------------------------------
  void ResourceManager::init()
  {
    // TODO: Bit of debug checking on the directory paths
    // TODO: Maybe actually change them to directories?
    // TODO: Auto find resource files
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShader(
    const std::string& vShaderRelativeFilePath,
    const std::string& fShaderRelativeFilePath,
    const std::string& gShaderRelativeFilePath,
    StringId name)
  {
    if (m_shaders.find(name) != m_shaders.end())
    {
      // If the shader already exists in our dictionary just return it rather than loading it
      return m_shaders[name];
    }

    Path vertexShader(m_vertexShaderDirectoryPath), fragmentShader(m_fragmentShaderDirectoryPath), geometryShader(m_geometryShaderDirectoryPath);
    vertexShader.combine(vShaderRelativeFilePath);
    fragmentShader.combine(fShaderRelativeFilePath);

    if (!gShaderRelativeFilePath.empty())
    {
      // Only set up the geometry shader path if we are using one
      geometryShader.combine(gShaderRelativeFilePath);
    }

    Shader* shader = loadShaderFromFile(vertexShader.asString(), fragmentShader.asString(), !gShaderRelativeFilePath.empty() ? geometryShader.asString() : "");
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
    if (m_textures.find(name) != m_textures.end())
    {
      // If the texture already exists in our dictionary then we just return it
      return m_textures[name];
    }

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
    const std::string& vertexShaderFullPath,
    const std::string& fragmentShaderFullPath,
    const std::string& geometryShaderFullPath)
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

    File file(vertexShaderFullPath);
    ASSERT(file.exists());
    file.read(vertexCode);

    file = File(fragmentShaderFullPath);
    ASSERT(file.exists());
    file.read(fragmentCode);

    if (!geometryShaderFullPath.empty())
    {
      file = File(geometryShaderFullPath);
      ASSERT(file.exists());
      file.read(geometryCode);
    }

    ASSERT(!vertexCode.empty());
    ASSERT(!fragmentCode.empty());
    ASSERT(geometryShaderFullPath.empty() || !geometryCode.empty());

    // Compile into the graphics card
    shader->compile(vertexCode, fragmentCode, !geometryShaderFullPath.empty() ? geometryCode : "");

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

    // Do some debug checking on the image path to make sure it exists
    ASSERT(File::exists(fullFilePath));

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

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadTextures()
  {
    // Clear all the references in our texture map
    m_textures.clear();

    // Resets our pooled memory
    m_texturePool.freeAll();

    // Clear the overflow
    m_textureOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadShaders()
  {
    // Clear all the references in our shader map
    m_shaders.clear();

    // Resets our pooled memory
    m_shaderPool.freeAll();

    // Clear the overflow
    m_shaderOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadAllAssets()
  {
    unloadTextures();
    unloadShaders();
  }

  //------------------------------------------------------------------------------------------------
  // Utility setters for the asset directory paths
  // The copy constructor for Path just copies the underlying string so is quick
  //------------------------------------------------------------------------------------------------
  void ResourceManager::setResourceDirectoryPath(const Path& resourceDirectoryPath)
  {
    m_resourceDirectoryPath = resourceDirectoryPath;
    
    Path newShaderPath(m_resourceDirectoryPath);
    newShaderPath.combine(SHADER_DIR);
    setShaderDirectoryPath(newShaderPath);

    Path newTexturePath(m_resourceDirectoryPath);
    newTexturePath.combine(TEXTURE_DIR);
    setTextureDirectoryPath(newTexturePath);
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setTextureDirectoryPath(const Path& textureDirectoryPath)
  {
    m_textureDirectoryPath = textureDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setShaderDirectoryPath(const Path& shaderDirectoryPath)
  {
    m_shaderDirectoryPath = shaderDirectoryPath;

    Path newVertexPath(m_shaderDirectoryPath);
    newVertexPath.combine(VERTEX_SHADER_DIR);
    setVertexShaderDirectoryPath(newVertexPath);

    Path newFragmentPath(m_shaderDirectoryPath);
    newFragmentPath.combine(FRAGMENT_SHADER_DIR);
    setFragmentShaderDirectoryPath(newFragmentPath);

    Path newGeomtryPath(m_shaderDirectoryPath);
    newGeomtryPath.combine(GEOMETRY_SHADER_DIR);
    setGeometryShaderDirectoryPath(newGeomtryPath);
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setVertexShaderDirectoryPath(const Path& vertexShaderDirectoryPath)
  {
    m_vertexShaderDirectoryPath = vertexShaderDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setFragmentShaderDirectoryPath(const Path& fragmentShaderDirectoryPath)
  {
    m_fragmentShaderDirectoryPath = fragmentShaderDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setGeometryShaderDirectoryPath(const Path& geometryShaderDirectoryPath)
  {
    m_geometryShaderDirectoryPath = geometryShaderDirectoryPath;
  }
}