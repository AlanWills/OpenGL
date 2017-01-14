#pragma once

#include "Objects/GameObject.h"
#include "Rendering/RenderManager.h"
#include "UI/UIManager.h"
#include "Memory/GapAllocator.h"


namespace OpenGL
{
#define SCREEN_GAMEOBJECT_POOL_SIZE 10

class Screen : public Component
{
  DECLARE_COMPONENT_WITH_MANAGER(GapAllocator, Screen, 10, ScreenManager);

  public:
    void initialize(Handle<Component> allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat elapsedGameTime) override;
    void render(GLfloat elapsedGameTime) override;
    void die() override;

    void addBackground(const std::string& backgroundImage);

    UIManager& getUIManager() { return m_uiManager; }
    const UIManager& getUIManager() const { return m_uiManager; }

  private:
    typedef Component Inherited;

    DECLARE_CLASS_COMPONENT_ALLOCATOR(GameObject, SCREEN_GAMEOBJECT_POOL_SIZE, m_gameObjects)

    /// \brief The manager responsible for handling all rendering in this screen
    RenderManager m_renderManager;

    /// \brief The manager responsible for handling all UI
    UIManager m_uiManager;
};

}