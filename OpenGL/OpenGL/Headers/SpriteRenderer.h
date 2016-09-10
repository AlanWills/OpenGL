#pragma once

#include "Component.h"
#include "Texture.h"
#include "Shader.h"

#include <memory>

class SpriteRenderer : public Component
{

public:
  SpriteRenderer(const std::string& textureAsset);
  ~SpriteRenderer();

  /// \brief Initializes gl drawing data for the texture
  void init() override;
  void update() override { }
  void draw(GLfloat percentageIntoFrame) const override;

private:
  std::unique_ptr<Shader> m_shader;
  std::unique_ptr<Texture> m_texture;
  std::unique_ptr<GLfloat> m_vertexAttributeData;

  GLuint m_vertexAttributeHandle;
  GLuint m_vertexBufferHandle;
};

