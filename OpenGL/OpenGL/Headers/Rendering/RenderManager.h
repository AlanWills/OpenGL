#pragma once

#include "Resources/Shader.h"
#include "Memory/ComponentAllocator.h"
#include "Objects/Component.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"


namespace OpenGL
{

#define SPRITERENDERER_POOLSIZE 10
#define TEXTRENDERER_POOLSIZE 10

class RenderManager : public Component
{
  public:
    RenderManager();
    ~RenderManager();

    void initialize() override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

    Handle<Shader> getSpriteShader() const { return m_spriteShader; }
    Handle<Shader> getTextShader() const { return m_textShader; }

    Handle<SpriteRenderer> allocateAndInitializeSpriteRenderer()
    {
      ASSERT(m_spriteRenderers.canAllocate());
      Handle<SpriteRenderer> spriteRenderer = m_spriteRenderers.allocate();
      spriteRenderer->initialize();
      return spriteRenderer;
    }

    void setProjectionMatrix(const glm::mat4& projectionMatrix) { m_projectionMatrix = projectionMatrix; }
    void setViewMatrix(const glm::mat4& viewMatrix) { m_viewMatrix = viewMatrix; }

  private:
    typedef Component Inherited;
    typedef ComponentAllocator<SpriteRenderer, SPRITERENDERER_POOLSIZE> SpriteRendererAllocator;
    typedef ComponentAllocator<TextRenderer, TEXTRENDERER_POOLSIZE> TextRendererAllocator;

    static StringId s_spriteShaderId;
    Handle<Shader> m_spriteShader;

    static StringId s_textShaderId;
    Handle<Shader> m_textShader;

    SpriteRendererAllocator m_spriteRenderers;
    TextRendererAllocator m_textRenderers;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
};

}