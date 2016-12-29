#pragma once

#include "Objects/GameObject.h"


namespace OpenGL
{
#define SCREEN_GAMEOBJECT_POOL_SIZE 10

class Screen : public Component
{
  DECLARE_COMPONENT_WITH_MANAGER(Screen, 10, ScreenManager);

  public:
    Screen();
    virtual ~Screen();

    void initialize() override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat elapsedGameTime) override;
    void render(GLfloat elapsedGameTime) override;
    void die() override;

  private:
    typedef Component Inherited;

    ComponentAllocator<GameObject, SCREEN_GAMEOBJECT_POOL_SIZE> m_gameObjects;
};

}