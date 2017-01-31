#include "stdafx.h"

#include "Resources/ResourceManager.h"
#include "Game/GameManager.h"

#include <SOIL/SOIL.h>


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ResourceManager::ResourceManager(const std::string& resourceDirectory) :
    m_resourceDirectoryPath(resourceDirectory),
    m_texture2DDirectoryPath(resourceDirectory),
    m_fontDirectoryPath(resourceDirectory),
    m_audioDirectoryPath(resourceDirectory),
    m_dataDirectoryPath(resourceDirectory),
    m_shaderDirectoryPath(resourceDirectory),
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
    // Load shader files
    {
      std::vector<File> shaderFiles;
      Directory::findFiles(m_vertexShaderDirectoryPath.as_string(), shaderFiles, ".vert", true);

      for (const File& file : shaderFiles)
      {
        const std::string& extensionlessFileName = file.getExtensionlessFileName();

        loadShader(extensionlessFileName + ".vert", extensionlessFileName + ".frag");
      }
    }

    // Load texture files
    {
      std::vector<File> textures;
      Directory::findFiles(m_texture2DDirectoryPath.as_string(), textures, ".png", true);

      for (const File& file : textures)
      {
        loadTexture(file.getFilePath().relativeTo(m_texture2DDirectoryPath));
      }
    }

    // Load font files
    {
      std::vector<File> fonts;
      Directory::findFiles(m_fontDirectoryPath.as_string(), fonts, ".ttf", true);

      for (const File& file : fonts)
      {
        loadFont(file.getFilePath().relativeTo(m_fontDirectoryPath));
      }
    }

    // Load audio files
    {
      std::vector<File> audio;
      Directory::findFiles(m_audioDirectoryPath.as_string(), audio, ".wav", true);

      for (const File& file : audio)
      {
        loadAudio(file.getFilePath().relativeTo(m_audioDirectoryPath));
      }
    }

    // Load data files
    {
      std::vector<File> data;
      Directory::findFiles(m_dataDirectoryPath.as_string(), data, ".xml", true);

      for (const File& file : data)
      {
        loadData(file.getFilePath().relativeTo(m_dataDirectoryPath));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  Handle<Shader> ResourceManager::loadShader(
    const std::string& vShaderRelativeFilePath,
    const std::string& fShaderRelativeFilePath)
  {
    const std::string& extensionlessFileName = File::getExtensionlessFileName(vShaderRelativeFilePath);
    ASSERT(extensionlessFileName == File::getExtensionlessFileName(fShaderRelativeFilePath));

    StringId name = internString(extensionlessFileName);

    if (m_shaders.find(name) != m_shaders.end())
    {
      // If the name already exists in our dictionary just return it rather than loading it
      return m_shaders[name];
    }

    Path vertexShader(m_vertexShaderDirectoryPath), fragmentShader(m_fragmentShaderDirectoryPath);
    vertexShader.combine(vShaderRelativeFilePath);
    fragmentShader.combine(fShaderRelativeFilePath);

    Handle<Shader> shader = loadShaderFromFile(vertexShader.as_string(), fragmentShader.as_string());
    m_shaders[name] = shader;
    return shader;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Texture2D> ResourceManager::loadTexture(const std::string& relativeFilePath, GLboolean alpha)
  {
    StringId name = internString(relativeFilePath);

    if (m_textures.find(name) != m_textures.end())
    {
      // If the name already exists in our dictionary then we just return it
      return m_textures[name];
    }

    Path fullPath(m_texture2DDirectoryPath);
    fullPath.combine(relativeFilePath);

    Handle<Texture2D> texture = loadTextureFromFile(fullPath.as_string(), alpha);
    m_textures[name] = texture;
    return texture;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Font> ResourceManager::loadFont(const std::string& relativeFilePath)
  {
    StringId name = internString(relativeFilePath);

    if (m_fonts.find(name) != m_fonts.end())
    {
      // If the name already exists in our dictionary then we just return it
      return m_fonts[name];
    }

    Path fullPath(m_fontDirectoryPath);
    fullPath.combine(relativeFilePath);

    Handle<Font> font = loadFontFromFile(fullPath.as_string());
    m_fonts[name] = font;
    return font;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Audio> ResourceManager::loadAudio(const std::string& relativeFilePath)
  {
    StringId name = internString(relativeFilePath);

    if (m_audio.find(name) != m_audio.end())
    {
      // If the name already exists in our dictionary then we just return it
      return m_audio[name];
    }

    Path fullPath(m_audioDirectoryPath);
    fullPath.combine(relativeFilePath);

    Handle<Audio> audio = loadAudioFromFile(fullPath.as_string());
    m_audio[name] = audio;
    return audio;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Data> ResourceManager::loadData(const std::string& relativeFilePath)
  {
    StringId name = internString(relativeFilePath);

    if (m_data.find(name) != m_data.end())
    {
      // If the name already exists in our dictionary then we just return it
      return m_data[name];
    }

    Path fullPath(m_dataDirectoryPath);
    fullPath.combine(relativeFilePath);

    const Handle<Data>& data = loadDataFromFile(fullPath.as_string());
    m_data[name] = data;
    return data;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Shader> ResourceManager::loadShaderFromFile(
    const std::string& vertexShaderFullPath,
    const std::string& fragmentShaderFullPath)
  {
    // Create shaderHandle object
    Handle<Shader> shaderHandle(nullptr);
    if (m_shaderPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      shaderHandle = m_shaderPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new shaderHandle and then store it in the overflow vector
      ASSERT_FAIL_MSG("Shader pool allocator out of memory.  Consider increasing the size.");
      Shader* shader = new Shader();

      // This isn't going to work - assigning address of temp variable
      shaderHandle = Handle<Shader>(&shader);
      m_shaderOverflow.push_back(std::unique_ptr<Shader>(shader));
    }

    ASSERT(shaderHandle.get());

    shaderHandle->load(vertexShaderFullPath, fragmentShaderFullPath);

    return shaderHandle;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Texture2D> ResourceManager::loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha)
  {
    // Create Texture object
    Handle<Texture2D> textureHandle(nullptr);
    if (m_texturePool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      textureHandle = m_texturePool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new textureHandle and then store it in the overflow vector
      ASSERT_FAIL_MSG("Texture pool allocator out of memory.  Consider increasing the size.");
      Texture2D* texture = new Texture2D();

      // This isn't going to work - assigning address of temp variable
      textureHandle = Handle<Texture2D>(&texture);
      m_textureOverflow.push_back(std::unique_ptr<Texture2D>(texture));
    }

    ASSERT(textureHandle.get());

    if (alpha)
    {
      textureHandle->setInternalFormat(GL_RGBA);
      textureHandle->setImageFormat(GL_RGBA);
    }

    // Do some debug checking on the image path to make sure it exists
    ASSERT(File::exists(fullFilePath));

    // Load the image

    int width, height;
    unsigned char* image = SOIL_load_image(fullFilePath.c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    ASSERT(image);

    // Now generate textureHandle
    textureHandle->generate(width, height, image);

    // And finally free image data
    SOIL_free_image_data(image);
    return textureHandle;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Font> ResourceManager::loadFontFromFile(const std::string& fullFilePath)
  {
    // Create Font object
    Handle<Font> fontHandle(nullptr);
    if (m_fontPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      fontHandle = m_fontPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new fontHandle and then store it in the overflow vector
      ASSERT_FAIL_MSG("Font pool allocator out of memory.  Consider increasing the size.");
      Font* font = new Font();

      // This isn't going to work - assigning address of temp variable
      fontHandle = Handle<Font>(&font);
      m_fontOverflow.push_back(std::unique_ptr<Font>(font));
    }

    ASSERT(fontHandle.get());

    fontHandle->generate(fullFilePath);
    return fontHandle;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Audio> ResourceManager::loadAudioFromFile(const std::string& fullFilePath)
  {
    // Create Audio object
    Handle<Audio> audioHandle(nullptr);
    if (m_audioPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      audioHandle = m_audioPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new AudioHandle and then store it in the overflow vector
      ASSERT_FAIL_MSG("Audio pool allocator out of memory.  Consider incremeneting the size.");
      Audio* audio = new Audio();

      // This isn't going to work - assigning address of temp variable
      audioHandle = Handle<Audio>(&audio);
      m_audioOverflow.push_back(std::unique_ptr<Audio>(audio));
    }

    ASSERT(audioHandle.get());

    audioHandle->generate(fullFilePath);
    return audioHandle;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Data> ResourceManager::loadDataFromFile(const std::string& fullFilePath)
  {
    // Create Data object
    Handle<Data> dataHandle(nullptr);
    if (m_dataPool.canAllocate())
    {
      // If we have room left in the pool we just allocate a new entry
      dataHandle = m_dataPool.allocate();
    }
    else
    {
      // If we have run out of room in our pool, we dynamically create a new AudioHandle and then store it in the overflow vector
      ASSERT_FAIL_MSG("Data pool allocator out of memory.  Consider incremeneting the size.");
      Data* data = new Data();

      // This isn't going to work - assigning address of temp variable
      dataHandle = Handle<Data>(&data);
      m_dataOverflow.push_back(std::unique_ptr<Data>(data));
    }

    ASSERT(dataHandle.get());

    dataHandle->generate(fullFilePath);
    return dataHandle;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadShaders()
  {
    // Clear all the references in our shaderHandle map
    m_shaders.clear();

    // Resets our pooled memory
    m_shaderPool.deallocateAll();

    // Clear the overflow
    m_shaderOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadTextures()
  {
    // Clear all the references in our textureHandle map
    m_textures.clear();

    // Resets our pooled memory
    m_texturePool.deallocateAll();

    // Clear the overflow
    m_textureOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadFonts()
  {
    // Clear all the references in our fontHandle map
    m_fonts.clear();

    // Resets our pooled memory
    m_fontPool.deallocateAll();

    // Clear the overflow
    m_fontOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadAudio()
  {
    // Clear all the references in our audio map
    m_audio.clear();

    // Resets our pooled memory
    m_audioPool.deallocateAll();

    // Clear the overflow
    m_audioOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadData()
  {
    // Clear all the references in our audio map
    m_data.clear();

    // Resets our pooled memory
    m_dataPool.deallocateAll();

    // Clear the overflow
    m_dataOverflow.clear();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadAllAssets()
  {
    unloadShaders();
    unloadTextures();
    unloadFonts();
    unloadAudio();
    unloadData();
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
      setTexture2DDirectoryPath(newTexturePath);
    }

    // Update font directory path
    {
      Path newFontPath(m_resourceDirectoryPath);
      newFontPath.combine(FONT_DIR);
      setFontDirectoryPath(newFontPath);
    }

    // Update audio directory path
    {
      Path newAudioPath(m_resourceDirectoryPath);
      newAudioPath.combine(AUDIO_DIR);
      setAudioDirectoryPath(newAudioPath);
    }

    // Update data directory path
    {
      Path newDataPath(m_resourceDirectoryPath);
      newDataPath.combine(DATA_DIR);
      setDataDirectoryPath(newDataPath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setAudioDirectoryPath(const Path& audioDirectoryPath)
  {
    m_audioDirectoryPath = audioDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setDataDirectoryPath(const Path& dataDirectoryPath)
  {
    m_dataDirectoryPath = dataDirectoryPath;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setTexture2DDirectoryPath(const Path& textureDirectoryPath)
  {
    m_texture2DDirectoryPath = textureDirectoryPath;
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

  //------------------------------------------------------------------------------------------------
  ResourceManager* getResourceManager()
  {
    return GameManager::getResourceManager();
  }
}