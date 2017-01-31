#pragma once

#include <map>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "Shader.h"
#include "Texture2D.h"
#include "Font.h"
#include "Audio.h"
#include "Data.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "StringInterning/StringId.h"

#include "Memory/GapAllocator.h"

using namespace Kernel;

namespace OpenGL
{

#define ASSETS_DIR "Assets"
#define AUDIO_DIR "Audio"
#define DATA_DIR "Data"
#define TEXTURE_DIR "Textures"
#define FONT_DIR "Fonts"
#define SHADER_DIR "Shaders"
#define VERTEX_SHADER_DIR "Vertex"
#define FRAGMENT_SHADER_DIR "Fragment"

// A class that hosts several functions to load Textures and Shaders. 
// Each loaded texture and/or shader is also stored for future reference by interned string handles. 
// All functions and resources are static and no public constructor is defined.
class ResourceManager
{
  public:
    ResourceManager(const std::string& resourceDirectory = Path(Directory::getExecutingAppDirectory(), ASSETS_DIR).as_string());
    ~ResourceManager();

    /// \brief Delete these for now - I don't think we should allow copy construction as it will really screw with the singlar ownership of this class with it's resources
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    /// \brief Initialises resource specific data including glew and file paths and loads all resources that will last the lifetime of the game
    void initialize();

    /// \brief Loads (and generates) a shader program from file by loading vertex and fragment shader source code. If gShaderFile is not nullptr, it also loads a geometry shader
    /// If the file has already been loaded, we simply return a handle to the loaded instance.
    /// The inputted filenames should be the names of the files relative to their corresponding shader directories, e.g. sprite.vert & sprite.frag
    Handle<Shader> loadShader(const std::string& vertexShaderRelativeFilePath, const std::string& fragmentShaderRelativeFilePath);

    /// \brief Loads (and generates) a texture from a file
    /// The inputted path should be relative to the texture directory
    Handle<Texture2D> loadTexture(const std::string& relativeFilePath, GLboolean alpha = GL_TRUE);

    /// \brief Loads (and generates) a texture from a file
    /// The inputted path should be relative to the font directory
    /// If the file has already been loaded, we simply return a handle to the loaded instance
    Handle<Font> loadFont(const std::string& relativeFilePath);

    /// \brief Loads (and generates) audio from a file
    /// The inputted path should relative to the audio directory
    /// If the file has already been loaded, we simply return a handle to the loaded instance
    Handle<Audio> loadAudio(const std::string& relativeFilePath);

    /// \brief Loads (and generates) data from a file
    /// The inputted path should relative to the data directory
    /// If the file has already been loaded, we simply return a handle to the loaded instance
    Handle<Data> loadData(const std::string& relativeFilePath);

    /// \brief Frees the relevant resources from the resource manager's memory
    void unloadShaders();
    void unloadTextures();
    void unloadFonts();
    void unloadAudio();
    void unloadData();
    void unloadAllAssets();

#define DEFINE_RESOURCE_DIRECTORY(ResourceType, MemberName) \
      public: \
        void set##ResourceType##DirectoryPath(const Path& ResourceType##DirectoryPath); \
        const Path& get##ResourceType##DirectoryPath() const { return MemberName; } \
      private: \
        Path MemberName;

    DEFINE_RESOURCE_DIRECTORY(Resource, m_resourceDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(Audio, m_audioDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(Data, m_dataDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(Texture2D, m_texture2DDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(Font, m_fontDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(Shader, m_shaderDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(VertexShader, m_vertexShaderDirectoryPath)
    DEFINE_RESOURCE_DIRECTORY(FragmentShader, m_fragmentShaderDirectoryPath)

  private:
    #define RESOURCE_TYPE_DEFS(ResourceType, PoolSize) \
      typedef std::map<StringId, Handle<ResourceType>>              ResourceType##Map; \
      typedef GapAllocator<ResourceType, PoolSize>                 ResourceType##Pool; \
      typedef std::vector<std::unique_ptr<ResourceType>>            ResourceType##PoolOverflow;

    RESOURCE_TYPE_DEFS(Shader, 10)
    RESOURCE_TYPE_DEFS(Texture2D, 100)
    RESOURCE_TYPE_DEFS(Font, 10)
    RESOURCE_TYPE_DEFS(Audio, 10)
    RESOURCE_TYPE_DEFS(Data, 10)

    /// \brief Loads and generates a shader from file.  Memory will be allocated so this class will already manage the object.
    Handle<Shader> loadShaderFromFile(
      const std::string& vertexShaderFullPath,
      const std::string& fragmentShaderFullPath);

    /// \brief Loads a single texture from file - requires the full texture file path as input.  Memory will be allocated so this class will already manage the object.
    Handle<Texture2D> loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha);

    /// \brief Loads a single font from file - requires the full font file path as input.  Memory will be allocated so this class will already manage the object.
    Handle<Font> loadFontFromFile(const std::string& fullFilePath);

    /// \brief Loads a single wav file - requires the full audio file path as input.  Memory will be allocated so this class will already manage the object.
    Handle<Audio> loadAudioFromFile(const std::string& fullFilePath);

    /// \brief Loads a single xml file - requires the full data file path as input.  Memory will be allocated so this class will already manage the object.
    Handle<Data> loadDataFromFile(const std::string& fullFilePath);

    // Resource storage
    ShaderMap     m_shaders;
    Texture2DMap  m_textures;
    FontMap       m_fonts;
    AudioMap      m_audio;
    DataMap       m_data;

    // Pre-allocated memory for resources - we can overrun this, but it will be less efficient as memory will have to be dynamically allocated.
    ShaderPool    m_shaderPool;
    Texture2DPool m_texturePool;
    FontPool      m_fontPool;
    AudioPool     m_audioPool;
    DataPool      m_dataPool;

    // The overflow vectors we use to store pointers to dynamically created resources
    // Ideally we want the pools to be large enough to never use these, but unexpected things may happen that we should account for
    ShaderPoolOverflow     m_shaderOverflow;
    Texture2DPoolOverflow  m_textureOverflow;
    FontPoolOverflow       m_fontOverflow;
    AudioPoolOverflow      m_audioOverflow;
    DataPoolOverflow       m_dataOverflow;
};

//------------------------------------------------------------------------------------------------
ResourceManager* getResourceManager();

}