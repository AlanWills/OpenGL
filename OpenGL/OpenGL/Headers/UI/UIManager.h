#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

class UIManager : public Component
{
  public:
    UIManager();
    ~UIManager();

    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

  private:
    typedef Component Inherited;
};

}