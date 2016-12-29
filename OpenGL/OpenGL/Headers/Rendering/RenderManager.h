#pragma once

#include "Resources/Shader.h"
#include "Memory/ComponentAllocator.h"
#include "Objects/Component.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"


namespace OpenGL
{

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

  private:
    typedef Component Inherited;

    static StringId s_spriteShaderId;
    Handle<Shader> m_spriteShader;

    static StringId s_textShaderId;
    Handle<Shader> m_textShader;
};

}