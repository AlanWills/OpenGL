#pragma once

#include "Resources/Shader.h"
#include "SpriteRenderer.h"
#include "Memory/ComponentAllocator.h"


namespace OpenGL
{

#define SPRITE_RENDERER_POOL_SIZE 10

class RenderManager
{
  public:
    RenderManager();
    ~RenderManager();

    void init();
    void render(GLfloat lag);

    Shader* getSpriteShader() const { return m_spriteShader; }

    SpriteRenderer* constructAndInitializeRenderer();
  
  private:
    static StringId s_spriteShaderId;
    Shader* m_spriteShader;

    ComponentAllocator<SpriteRenderer, SPRITE_RENDERER_POOL_SIZE> m_spriteRenderers;
};

}