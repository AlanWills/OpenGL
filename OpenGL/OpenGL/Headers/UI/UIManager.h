#pragma once

#include "Objects/Component.h"
#include "Resources/Shader.h"


namespace OpenGL
{

class UIManager : public Component
{
  public:
    UIManager();
    virtual ~UIManager();

    void initialize() override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

  private:
    typedef Component Inherited;

    static StringId s_spriteShaderId;
    Handle<Shader> m_spriteShader;

    static StringId s_textShaderId;
    Handle<Shader> m_textShader;
};

}