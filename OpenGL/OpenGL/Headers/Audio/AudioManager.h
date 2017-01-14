#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

class AudioManager : public Component
{
  public:
    AudioManager();
    virtual ~AudioManager();

    void initialize(Handle<Component> allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

  private:
    typedef Component Inherited;
};

}