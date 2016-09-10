#pragma once

#include <unordered_map>
#include <string>

#include <GL/glew.h>

#include "Texture.h"
#include "Shader.h"

#define SHADER_DIR "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\Shaders\\"
#define VERTEX_DIR "Vertex\\"
#define FRAGMENT_DIR "Fragment\\"
#define GEOMETRY_DIR "Geometry\\"
#define TEXTURE_DIR "C:\\Users\\Alan\\Documents\\Visual Studio 2015\\Projects\\OpenGL\\OpenGL\\OpenGL\\Assets\\"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
  // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
  static Shader* loadShader(const std::string& name, const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

  // Retrieves a stored shader
  static Shader* getShader(const std::string& name);

  // Loads (and generates) a texture from file using a filepath relative to the TEXTURE_DIR
  static Texture* loadTexture(const GLchar *file, GLboolean alpha, const std::string& name);

  // Retrieves a stored texture
  static Texture* getTexture(const std::string& name);

  /// \brief Properly deallocates all of the resources
  static void freeResources();

private:
  /// \brief Private constructor for singleton class
  ResourceManager() { }

  /// \brief Loads and generates a shader from a file
  static Shader* loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
  static bool readShaderFile(const GLchar* shaderFilePath, std::string& shaderCodeOutput);

  /// \brief Loads a single texture from file
  static Texture* loadTextureFromFile(const GLchar* file, GLboolean alpha);

  static std::unordered_map<std::string, Shader*> m_shaders;
  static std::unordered_map<std::string, Texture*> m_textures;
};

