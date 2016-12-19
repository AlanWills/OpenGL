#pragma once

#include "Resources/Shader.h"
#include "Memory/ComponentAllocator.h"
#include "Objects/Component.h"


namespace OpenGL
{

class RenderManager : public Component
{
  public:
    RenderManager();
    ~RenderManager();

    void initialize() override;
    void render(GLfloat lag) override;

    Shader* getSpriteShader() const { return m_spriteShader; }

  private:
    typedef Component Inherited;

    static StringId s_spriteShaderId;
    Shader* m_spriteShader;
};

}