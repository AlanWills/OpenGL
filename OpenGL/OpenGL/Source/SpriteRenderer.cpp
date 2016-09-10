#include "SpriteRenderer.h"
#include "Camera.h"

//------------------------------------------------------------------------------------------------
SpriteRenderer::SpriteRenderer(const std::string& textureAsset)
: m_shader(new Shader()),
  m_texture(nullptr),
  m_vertexAttributeData(nullptr)
{
  m_texture.reset(new Texture());
}

//------------------------------------------------------------------------------------------------
SpriteRenderer::~SpriteRenderer()
{
}

//------------------------------------------------------------------------------------------------
void SpriteRenderer::init()
{
  m_vertexAttributeData.reset(
    new GLfloat[36] {
      // Pos      // Tex(swapped y coordinates because texture is flipped upside down)
      0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
      0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
      1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

      0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
      1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
      1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    }
  );

  glGenVertexArrays(1, &m_vertexAttributeHandle);
  glGenBuffers(1, &m_vertexBufferHandle);
  glBindVertexArray(m_vertexAttributeHandle);
  {
    auto size = sizeof(m_vertexAttributeData.get());
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 36, m_vertexAttributeData.get(), GL_STATIC_DRAW);

    // Position and texture
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
}

//------------------------------------------------------------------------------------------------
void SpriteRenderer::draw(GLfloat percentageIntoFrame) const
{
  //// Camera matrices
  //glm::mat4 projection, view, model;
  //Camera::getInstance().getProjectionMatrix(800, 600, projection);
  //Camera::getInstance().getViewMatrix(view);

  //// Ready gl to use this shader and bind the view and projection matrices to the uniform shader variables
  //m_shader->useShader(view, projection);

  //model = glm::translate(model, glm::vec3(0, 0, 0));

  //glBindVertexArray(m_vertexAttributeHandle);
  //m_shader->bindUniformMatrix(model, MODEL_MATRIX);
  //m_shader->bindUniformTexture(GL_TEXTURE0, m_texture.get(), "objectTexture", 0);

  //glDrawArrays(GL_TRIANGLES, 0, 6);
  //glBindVertexArray(0);
}