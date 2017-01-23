#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

class PhysicsManager : public Component
{
  public:
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

  private:
    typedef Component Inherited;
};

}