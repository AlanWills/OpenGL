#pragma once

#include <map>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "Texture2D.h"
#include "Shader.h"
#include "DllExport.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "StringInterning/StringId.h"

#include "Memory/PoolAllocator.h"

using namespace Kernel;

namespace Engine
{

#define TEXTURE_DIR "Assets"
#define SHADER_DIR "Shaders"
#define LEVEL_DIR "Levels"
#define VERTEX_SHADER_DIR "Vertex"
#define FRAGMENT_SHADER_DIR "Fragment"

#define SHADER_POOL_SIZE 10
#define TEXTURE_POOL_SIZE 100

typedef std::map<StringId, Shader*>                     ShaderMap;
typedef PoolAllocator<Shader, SHADER_POOL_SIZE>         ShaderPool;
typedef std::vector<std::unique_ptr<Shader>>            ShaderPoolOverflow;

typedef std::map<StringId, Texture2D*>                  TextureMap;
typedef PoolAllocator<Texture2D, TEXTURE_POOL_SIZE>     TexturePool;
typedef std::vector<std::unique_ptr<Texture2D>>         TexturePoolOverflow;

namespace ResourceStringIds
{
  static const StringId SpriteShader = internString("sprite");
}

// A class that hosts several functions to load Textures and Shaders. 
// Each loaded texture and/or shader is also stored for future reference by interned string handles. 
// All functions and resources are static and no public constructor is defined.
class DllExport ResourceManager
{
  public:
    ResourceManager(const std::string& resourceDirectory = Directory::getExecutingAppDirectory());
    ~ResourceManager();

    /// \brief Delete these for now - I don't think we should allow copy construction as it will really screw with the singlar ownership of this class with it's resources
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    /// \brief Initialises resource specific data including glew and file paths and loads all resources that will last the lifetime of the game
    void init();

    /// \brief Loads (and generates) a shader program from file by loading vertex and fragment shader source code. If gShaderFile is not nullptr, it also loads a geometry shader
    Shader* loadShader(
      const std::string& vShaderRelativeFilePath, 
      const std::string& fShaderRelativeFilePath, 
      StringId name);

    /// \brief Retrieves a stored shader
    Shader* getShader(StringId name);

    /// \brief Loads (and generates) a texture from a file
    /// The inputted path should be relative to the texture directory
    Texture2D* loadTexture(const std::string& relativeFilePath, GLboolean alpha, StringId name);

    /// \brief Retrieves a stored texture
    Texture2D* getTexture(StringId name);

    /// \brief These setters allow changing the location of the common asset folders on disc
    /// However, since the static variables representing these locations form a tree, changing certain ones requires changing others - these functions take care of this
    /// As a result, these are non-trivial and we cannot simplify by exposing the variables globally for fear of invalidating the others on change
    void setResourceDirectoryPath(const Path& resourceDirectoryPath);
    void setTextureDirectoryPath(const Path& textureDirectoryPath);
    void setShaderDirectoryPath(const Path& shaderDirectoryPath);
    void setVertexShaderDirectoryPath(const Path& vertexShaderDirectoryPath);
    void setFragmentShaderDirectoryPath(const Path& fragmentShaderDirectoryPath);
    
    /// \brief Getters for the common asset folders on disc
    const Path& getResourceDirectoryPath() { return m_resourceDirectoryPath; }
    const Path& getTextureDirectoryPath() { return m_textureDirectoryPath; }
    const Path& getShaderDirectoryPath() { return m_shaderDirectoryPath; }
    const Path& getVertexShaderDirectoryPath() { return m_vertexShaderDirectoryPath; }
    const Path& getFragmentShaderDirectoryPath() { return m_fragmentShaderDirectoryPath; }

    /// \brief Frees the relevant resources from the resource manager's memory
    void unloadTextures();
    void unloadShaders();
    void unloadAllAssets();

  private:
    // Loads and generates a shader from file
    Shader* loadShaderFromFile(
      const std::string& vertexShaderFullPath,
      const std::string& fragmentShaderFullPath);

    /// \brief Loads a single texture from file - requires the full texture file path as input
    Texture2D* loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha);

    // Resource storage
    ShaderMap   m_shaders;
    TextureMap  m_textures;

    // Pre-allocated memory for resources - we can overrun this, but it will be less efficient as memory will have to be dynamically allocated.
    ShaderPool  m_shaderPool;
    TexturePool m_texturePool;

    // The overflow vectors we use to store pointers to dynamically created resources
    // Ideally we want the X_POOL_SIZE to be large enough to never use these, but unexpected things may happen that we should account for
    ShaderPoolOverflow   m_shaderOverflow;
    TexturePoolOverflow  m_textureOverflow;

    // Static variables representing the paths to commonly used resource directories
    // They can be changed by the appropriate set functions, but since they represent a directory tree
    // Updating a higher level directory requires updating lower level directory paths too
    // As a result, the setters are not trivial and we cannot just expose these as global variables for risk of invalidating some variables by changing others
    Path     m_resourceDirectoryPath;
    Path     m_textureDirectoryPath;
    Path     m_shaderDirectoryPath;
    Path     m_vertexShaderDirectoryPath;
    Path     m_fragmentShaderDirectoryPath;
};

}