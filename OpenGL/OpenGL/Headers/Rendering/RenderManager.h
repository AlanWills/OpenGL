#pragma once

#include "Resources/Shader.h"
#include "Objects/Component.h"


namespace OpenGL
{

class RenderManager : public Component
{
  public:
    RenderManager();

    void initialize(const Handle<Component>& allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

    Handle<Shader> getSpriteShader() const { return m_spriteShader; }
    Handle<Shader> getTextShader() const { return m_textShader; }

  private:
    typedef Component Inherited;

    Handle<Shader> m_spriteShader;
    Handle<Shader> m_textShader;
};

}