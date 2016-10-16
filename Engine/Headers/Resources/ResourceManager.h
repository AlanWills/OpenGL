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

#ifdef WIN32
#define DIRECTORY ""
#else
#define DIRECTORY ""
#endif
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

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class DllExport ResourceManager
{
  public:
    /// \brief Initialises resource specific data including glew and file paths and loads all resources that will last the lifetime of the game
    static void init();

    /// \brief Loads (and generates) a shader program from file by loading vertex and fragment shader source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader* loadShader(
      const std::string& vShaderRelativeFilePath, 
      const std::string& fShaderRelativeFilePath, 
      StringId name);

    /// \brief Retrieves a stored shader
    static Shader* getShader(StringId name);

    /// \brief Loads (and generates) a texture from a file
    /// The inputted path should be relative to the texture directory
    static Texture2D* loadTexture(const std::string& relativeFilePath, GLboolean alpha, StringId name);

    /// \brief Retrieves a stored texture
    static Texture2D* getTexture(StringId name);

    /// \brief These setters allow changing the location of the common asset folders on disc
    /// However, since the static variables representing these locations form a tree, changing certain ones requires changing others - these functions take care of this
    /// As a result, these are non-trivial and we cannot simplify by exposing the variables globally for fear of invalidating the others on change
    static void setResourceDirectoryPath(const Path& resourceDirectoryPath);
    static void setTextureDirectoryPath(const Path& textureDirectoryPath);
    static void setShaderDirectoryPath(const Path& shaderDirectoryPath);
    static void setVertexShaderDirectoryPath(const Path& vertexShaderDirectoryPath);
    static void setFragmentShaderDirectoryPath(const Path& fragmentShaderDirectoryPath);
    
    /// \brief Getters for the common asset folders on disc
    static const Path& getResourceDirectoryPath() { return m_resourceDirectoryPath; }
    static const Path& getTextureDirectoryPath() { return m_textureDirectoryPath; }
    static const Path& getShaderDirectoryPath() { return m_shaderDirectoryPath; }
    static const Path& getVertexShaderDirectoryPath() { return m_vertexShaderDirectoryPath; }
    static const Path& getFragmentShaderDirectoryPath() { return m_fragmentShaderDirectoryPath; }

    /// \brief Frees the relevant resources from the resource manager's memory
    static void unloadTextures();
    static void unloadShaders();
    static void unloadAllAssets();

  private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }

    // Loads and generates a shader from file
    static Shader* loadShaderFromFile(
      const std::string& vertexShaderFullPath,
      const std::string& fragmentShaderFullPath);

    /// \brief Loads a single texture from file - requires the full texture file path as input
    static Texture2D* loadTextureFromFile(const std::string& fullFilePath, GLboolean alpha);

    // Resource storage
    static ShaderMap   m_shaders;
    static TextureMap  m_textures;

    // Pre-allocated memory for resources - we can overrun this, but it will be less efficient as memory will have to be dynamically allocated.
    static ShaderPool  m_shaderPool;
    static TexturePool m_texturePool;

    // The overflow vectors we use to store pointers to dynamically created resources
    // Ideally we want the X_POOL_SIZE to be large enough to never use these, but unexpected things may happen that we should account for
    static ShaderPoolOverflow   m_shaderOverflow;
    static TexturePoolOverflow  m_textureOverflow;

    // Static variables representing the paths to commonly used resource directories
    // They can be changed by the appropriate set functions, but since they represent a directory tree
    // Updating a higher level directory requires updating lower level directory paths too
    // As a result, the setters are not trivial and we cannot just expose these as global variables for risk of invalidating some variables by changing others
    static Path     m_resourceDirectoryPath;
    static Path     m_textureDirectoryPath;
    static Path     m_shaderDirectoryPath;
    static Path     m_vertexShaderDirectoryPath;
    static Path     m_fragmentShaderDirectoryPath;
};

}