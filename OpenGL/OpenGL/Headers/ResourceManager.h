#pragma once

#include <map>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "Texture2D.h"
#include "Shader.h"

#define DIRECTORY "C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/"
#define TEXTURE_DIR "Assets/"
#define SHADER_DIR "Shaders/"
#define VERTEX_SHADER_DIR "Vertex/"
#define FRAGMENT_SHADER_DIR "Fragment/"
#define GEOMETRY_SHADER_DIR "Geometry/"

typedef std::map<std::string, std::unique_ptr<Shader>>     ShaderMap;
typedef std::map<std::string, std::unique_ptr<Texture2D>>  TextureMap;

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
  // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
  static Shader* loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, const std::string& name);

  // Retrieves a stored shader
  static Shader* getShader(const std::string& name);

  // Loads (and generates) a texture from file
  static Texture2D* loadTexture(const GLchar *file, GLboolean alpha, const std::string& name);

  // Retrieves a stored texture
  static Texture2D* getTexture(const std::string& name);

private:
  // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
  ResourceManager() { }

  // Loads and generates a shader from file
  static Shader* loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

  // Reads a file locatted at the inputted file path and stores the file contents in the outputFileText parameter
  static void readFile(const GLchar* filePath, std::string& outputFileText);

  // Loads a single texture from file
  static Texture2D* loadTextureFromFile(const GLchar *file, GLboolean alpha);

  // Resource storage
  static ShaderMap   m_shaders;
  static TextureMap  m_textures;
};