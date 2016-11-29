#pragma once

#include "DllExport.h"
#include "GLHeaders.h"
#include "Resources/Texture2D.h"
#include "Resources/Shader.h"

#include <string>

namespace Engine
{
// A class which is responsible for rendering a texture using the sprite shader
class DllExport SpriteRenderer
{
  public:
    SpriteRenderer();
    ~SpriteRenderer();

    /// \brief Set up the gl buffers and load the texture and shader from the resource manager
    void init(StringId textureName);

    void render(GLfloat lag, const glm::mat4& modelMatrix);

  private:
    static StringId s_spriteShaderId;

    Texture2D* m_texture;
    Shader* m_shader;

    glm::vec4 m_colour;

    GLuint m_vbo;
    GLuint m_vao;
};

}