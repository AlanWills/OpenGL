#pragma once

#include <map>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "Shader.h"
#include "Texture2D.h"
#include "Font.h"
#include "Audio.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "StringInterning/StringId.h"

#include "Memory/PoolAllocator.h"

using namespace Kernel;

namespace OpenGL
{

#define ASSETS_DIR "Assets"
#define AUDIO_DIR "Audio"
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

    /// \brief These setters allow changing the location of the common asset folders on disc
    /// However, since the static variables representing these locations form a tree, changing certain ones requires changing others - these functions take care of this
    /// As a result, these are non-trivial and we cannot simplify by exposing the variables globally for fear of invalidating the others on change
    void setResourceDirectoryPath(const Path& resourceDirectoryPath);
    void setAudioDirectoryPath(const Path& audioDirectoryPath);
    void setTextureDirectoryPath(const Path& textureDirectoryPath);
    void setFontDirectoryPath(const Path& fontDirectoryPath);
    void setShaderDirectoryPath(const Path& shaderDirectoryPath);
    void setVertexShaderDirectoryPath(const Path& vertexShaderDirectoryPath);
    void setFragmentShaderDirectoryPath(const Path& fragmentShaderDirectoryPath);
    
    /// \brief Getters for the common asset folders on disc
    const Path& getResourceDirectoryPath() const { return m_resourceDirectoryPath; }
    const Path& getAudioDirectoryPath() const { return m_audioDirectoryPath; }
    const Path& getTextureDirectoryPath() const { return m_textureDirectoryPath; }
    const Path& getFontDirectoryPath() const { return m_fontDirectoryPath; }
    const Path& getShaderDirectoryPath() const { return m_shaderDirectoryPath; }
    const Path& getVertexShaderDirectoryPath() const { return m_vertexShaderDirectoryPath; }
    const Path& getFragmentShaderDirectoryPath() const { return m_fragmentShaderDirectoryPath; }

    /// \brief Frees the relevant resources from the resource manager's memory
    void unloadShaders();
    void unloadTextures();
    void unloadFonts();
    void unloadAudio();
    void unloadAllAssets();

  private:
    typedef std::map<StringId, Handle<Shader>>              ShaderMap;
    typedef PoolAllocator<Shader, 10>                       ShaderPool;
    typedef std::vector<std::unique_ptr<Shader>>            ShaderPoolOverflow;

    typedef std::map<StringId, Handle<Texture2D>>           TextureMap;
    typedef PoolAllocator<Texture2D, 100>                   TexturePool;
    typedef std::vector<std::unique_ptr<Texture2D>>         TexturePoolOverflow;

    typedef std::map<StringId, Handle<Font>>                FontMap;
    typedef PoolAllocator<Font, 10>                         FontPool;
    typedef std::vector<std::unique_ptr<Font>>              FontPoolOverflow;

    typedef std::map<StringId, Handle<Audio>>               AudioMap;
    typedef PoolAllocator<Audio, 10>                        AudioPool;
    typedef std::vector<std::unique_ptr<Audio>>             AudioPoolOverflow;

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

    // Resource storage
    ShaderMap   m_shaders;
    TextureMap  m_textures;
    FontMap     m_fonts;
    AudioMap    m_audio;

    // Pre-allocated memory for resources - we can overrun this, but it will be less efficient as memory will have to be dynamically allocated.
    ShaderPool  m_shaderPool;
    TexturePool m_texturePool;
    FontPool    m_fontPool;
    AudioPool   m_audioPool;

    // The overflow vectors we use to store pointers to dynamically created resources
    // Ideally we want the pools to be large enough to never use these, but unexpected things may happen that we should account for
    ShaderPoolOverflow   m_shaderOverflow;
    TexturePoolOverflow  m_textureOverflow;
    FontPoolOverflow     m_fontOverflow;
    AudioPoolOverflow    m_audioOverflow;

    // Static variables representing the paths to commonly used resource directories
    // They can be changed by the appropriate set functions, but since they represent a directory tree
    // Updating a higher level directory requires updating lower level directory paths too
    // As a result, the setters are not trivial and we cannot just expose these as global variables for risk of invalidating some variables by changing others
    Path     m_resourceDirectoryPath;
    Path     m_audioDirectoryPath;
    Path     m_textureDirectoryPath;
    Path     m_fontDirectoryPath;
    Path     m_shaderDirectoryPath;
    Path     m_vertexShaderDirectoryPath;
    Path     m_fragmentShaderDirectoryPath;
};

}