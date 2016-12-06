#pragma once

#include "Resources/Shader.h"
#include "SpriteRenderer.h"
#include "Memory/PoolAllocator.h"


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
  
  private:
    static StringId s_spriteShaderId;

    PoolAllocator<SpriteRenderer, SPRITE_RENDERER_POOL_SIZE> m_spriteRenderers;
    Shader* m_shader;
};

}