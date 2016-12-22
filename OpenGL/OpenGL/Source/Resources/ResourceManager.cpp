#include "stdafx.h"

#include "Resources/ResourceManager.h"

#include <SOIL/SOIL.h>


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ResourceManager::ResourceManager(const std::string& resourceDirectory) :
    m_resourceDirectoryPath(resourceDirectory),
    m_shaderDirectoryPath(resourceDirectory),
    m_textureDirectoryPath(resourceDirectory),
    m_fontDirectoryPath(resourceDirectory),
    m_vertexShaderDirectoryPath(resourceDirectory),
    m_fragmentShaderDirectoryPath(resourceDirectory)
  {
    // This will set all the paths up correctly
    setResourceDirectoryPath(resourceDirectory);
  }

  //------------------------------------------------------------------------------------------------
  ResourceManager::~ResourceManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::initialize()
  {
    std::vector<File> shaderFiles;
    Directory::findFiles(m_vertexShaderDirectoryPath.asString(), shaderFiles, ".vs", true);

    for (const File& file : shaderFiles)
    {
      const std::string& extensionlessFileName = file.getExtensionlessFileName();

      loadShader(extensionlessFileName + ".vs", extensionlessFileName + ".frag", internString(extensionlessFileName));
    }

    std::vector<File> textures;
    Directory::findFiles(m_textureDirectoryPath.asString(), textures, ".", true);

    for (const File& file : textures)
    {
      loadTexture(file.getFileName(), GL_TRUE, internString(file.getExtensionlessFileName()));
    }

    std::vector<File> fonts;
    Directory::findFiles(m_fontDirectoryPath.asString(), fonts, ".ttf", true);

    for (const File& file : fonts)
    {
      loadFont(file.getFileName(), internString(file.getExtensionlessFileName()));
    }
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShader(
    const std::string& vShaderRelativeFilePath,
    const std::string& fShaderRelativeFilePath,
    StringId name)
  {
    if (m_shaders.find(name) != m_shaders.end())
    {
      // If the shader already exists in our dictionary just return it rather than loading it
      return m_shaders[name];
    }

    Path vertexShader(m_vertexShaderDirectoryPath), fragmentShader(m_fragmentShaderDirectoryPath);
    vertexShader.combine(vShaderRelativeFilePath);
    fragmentShader.combine(fShaderRelativeFilePath);

    Shader* shader = loadShaderFromFile(vertexShader.asString(), fragmentShader.asString());
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
  Font* ResourceManager::loadFont(const std::string& relativeFilePath, StringId name)
  {
    if (m_fonts.find(name) != m_fonts.end())
    {
      // If the texture already exists in our dictionary then we just return it
      return m_fonts[name];
    }

    Path fullPath(m_fontDirectoryPath);
    fullPath.combine(relativeFilePath);

    Font* font = loadFontFromFile(fullPath.asString());
    m_fonts[name] = font;
    return font;
  }

  //------------------------------------------------------------------------------------------------
  Font* ResourceManager::getFont(StringId name)
  {
    if (m_fonts.find(name) == m_fonts.end())
    {
      ASSERT_FAIL_MSG("Font does not exist");

      /// TODO: Return a default font or something?
      return nullptr;
    }

    return m_fonts[name];
  }

  //------------------------------------------------------------------------------------------------
  Shader* ResourceManager::loadShaderFromFile(
    const std::string& vertexShaderFullPath,
    const std::string& fragmentShaderFullPath)
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
      ASSERT_FAIL_MSG("Shader pool allocator out of memory.  Consider increasing the size.")
      shader = new Shader();
      m_shaderOverflow.push_back(std::unique_ptr<Shader>(shader));
    }

    ASSERT(shader);

    shader->load(vertexShaderFullPath, fragmentShaderFullPath);

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
      ASSERT_FAIL_MSG("Texture pool allocator out of memory.  Consider increasing the size.")
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
  Font* ResourceManager::loadFontFromFile(const std::string& fullFilePath)
  {
    // Create Font object
    Font* font = nullptr;
    if (m_fontPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      font = m_fontPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new font and then store it in the overflow vector
      ASSERT_FAIL_MSG("Font pool allocator out of memory.  Consider increasing the size.")
      font = new Font();
      m_fontOverflow.push_back(std::unique_ptr<Font>(font));
    }

    ASSERT(font);
    font->generate(fullFilePath);

    return font;
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
  void ResourceManager::unloadFonts()
  {
    // Clear all the references in our font map
    m_fonts.clear();

    // Resets our pooled memory
    m_fontPool.freeAll();

    // Clear the overflow
    m_fontOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadAllAssets()
  {
    unloadShaders();
    unloadTextures();
    unloadFonts();
  }

  //------------------------------------------------------------------------------------------------
  // Utility setters for the asset directory paths
  // The copy constructor for Path just copies the underlying string so is quick
  //------------------------------------------------------------------------------------------------
  void ResourceManager::setResourceDirectoryPath(const Path& resourceDirectoryPath)
  {
    m_resourceDirectoryPath = resourceDirectoryPath;
    
    // Update shader directory path
    {
      Path newShaderPath(m_resourceDirectoryPath);
      newShaderPath.combine(SHADER_DIR);
      setShaderDirectoryPath(newShaderPath);
    }

    // Update texture directory path
    {
      Path newTexturePath(m_resourceDirectoryPath);
      newTexturePath.combine(TEXTURE_DIR);
      setTextureDirectoryPath(newTexturePath);
    }

    // Update font directory path
    {
      Path newFontPath(m_resourceDirectoryPath);
      newFontPath.combine(FONT_DIR);
      setFontDirectoryPath(newFontPath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setTextureDirectoryPath(const Path& textureDirectoryPath)
  {
    m_textureDirectoryPath = textureDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setFontDirectoryPath(const Path& fontDirectoryPath)
  {
    m_fontDirectoryPath = fontDirectoryPath;
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
}