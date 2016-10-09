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
#define DIRECTORY "../OpenGL"
#define TEXTURE_DIR "Assets"
#define SHADER_DIR "Shaders"
#define LEVEL_DIR "Levels"
#define VERTEX_SHADER_DIR "Vertex"
#define FRAGMENT_SHADER_DIR "Fragment"
#define GEOMETRY_SHADER_DIR "Geometry"

#define SHADER_POOL_SIZE 10
#define TEXTURE_POOL_SIZE 100

typedef std::map<StringId, Shader*>                     ShaderMap;
typedef PoolAllocator<Shader, SHADER_POOL_SIZE>         ShaderPool;
typedef std::vector<std::unique_ptr<Shader>>            ShaderPoolOverflow;

typedef std::map<StringId, Texture2D*>                  TextureMap;
typedef PoolAllocator<Texture2D, TEXTURE_POOL_SIZE>     TexturePool;
typedef std::vector<std::unique_ptr<Texture2D>>         TexturePoolOverflow;

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

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader* loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, StringId name);

    // Retrieves a stored shader
    static Shader* getShader(StringId name);

    // Loads (and generates) a texture from file
    static Texture2D* loadTexture(const GLchar *file, GLboolean alpha, StringId name);

    // Retrieves a stored texture
    static Texture2D* getTexture(StringId name);

  private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }

    // Loads and generates a shader from file
    static Shader* loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

    // Loads a single texture from file
    static Texture2D* loadTextureFromFile(const GLchar *file, GLboolean alpha);

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
};

}