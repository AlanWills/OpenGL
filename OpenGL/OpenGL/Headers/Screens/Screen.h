#pragma once

#include "Objects/GameObject.h"
#include "Rendering/RenderManager.h"
#include "UI/UIManager.h"


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

    /// \brief The manager responsible for handling all rendering in this screen
    RenderManager m_renderManager;

    /// \brief The manager responsible for handling all UI
    UIManager m_uiManager;
};

}