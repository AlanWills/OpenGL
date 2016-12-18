#pragma once

#include "Resources/Shader.h"
#include "SpriteRenderer.h"
#include "Memory/ComponentAllocator.h"


namespace OpenGL
{

#define SPRITE_RENDERER_POOL_SIZE 10

class RenderManager : public Component
{
  public:
    RenderManager();
    ~RenderManager();

    void initialize() override;
    void render(GLfloat lag) override;

    Shader* getSpriteShader() const { return m_spriteShader; }

    SpriteRenderer* allocateAndInitializeRenderer();
  
  private:
    typedef Component Inherited;

    static StringId s_spriteShaderId;
    Shader* m_spriteShader;

    ComponentAllocator<SpriteRenderer, SPRITE_RENDERER_POOL_SIZE> m_spriteRenderers;
};

}