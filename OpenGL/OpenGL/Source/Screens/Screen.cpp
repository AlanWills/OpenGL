#include "stdafx.h"

#include "Screens/Screen.h"
#include "Game/GameManager.h"
#include "Scripts/ScriptManager.h"
#include "Scripts/KeyboardMovementScript.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{
  REGISTER_COMPONENT(Screen);

  //------------------------------------------------------------------------------------------------
  Screen::Screen()
  {
  }

  //------------------------------------------------------------------------------------------------
  Screen::~Screen()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Screen::initialize()
  {
    Inherited::initialize();

    m_screenRenderManager.initialize();
    m_worldRenderManager.initialize();

    Handle<GameObject> gameObject = m_gameObjects.allocateAndInitialize();
    
    Handle<SpriteRenderer> spriteRenderer = gameObject->addComponent(m_worldRenderManager.allocateAndInitializeSpriteRenderer());
    spriteRenderer->setTexture("Fiirkan");
    spriteRenderer->setTransform(&gameObject->getTransform());

    Handle<GameObject> gameObject2 = m_gameObjects.allocateAndInitialize();

    Handle<SpriteRenderer> spriteRenderer2 = gameObject2->addComponent(m_screenRenderManager.allocateAndInitializeSpriteRenderer());
    spriteRenderer2->setTexture("ButtonDefault");
    spriteRenderer2->setTransform(&gameObject2->getTransform());

    gameObject2->getTransform().translate(glm::vec3(0, 0, -0.1f));
    
    Handle<KeyboardMovementScript> movementScript = gameObject->addComponent(KeyboardMovementScript::allocateAndInitialize());
    movementScript->setTransform(&gameObject->getTransform());
    movementScript->setMoveDownKey(GLFW_KEY_DOWN);
    movementScript->setMoveUpKey(GLFW_KEY_UP);
    movementScript->setMoveLeftKey(GLFW_KEY_LEFT);
    movementScript->setMoveRightKey(GLFW_KEY_RIGHT);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::awake()
  {
    Inherited::awake();

    m_screenRenderManager.awake();
    m_worldRenderManager.awake();

    m_gameObjects.awake();
  }

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_screenRenderManager.handleInput(elapsedGameTime);
    m_worldRenderManager.handleInput(elapsedGameTime);

    m_gameObjects.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_screenRenderManager.update(secondsPerUpdate);
    m_worldRenderManager.update(secondsPerUpdate);

    m_gameObjects.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::render(GLfloat lag)
  {
    Inherited::render(lag);

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();

    m_screenRenderManager.setProjectionMatrix(camera->getOrthographicProjectionMatrix());
    m_screenRenderManager.setViewMatrix(glm::mat4());

    m_worldRenderManager.setProjectionMatrix(camera->getPerspectiveProjectionMatrix());
    m_worldRenderManager.setViewMatrix(camera->getViewMatrix());

    // Draw world
    m_worldRenderManager.render(lag);
    m_gameObjects.render(lag);

    // Draw screen overlay
    m_screenRenderManager.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::die()
  {
    Inherited::die();

    m_screenRenderManager.die();
    m_worldRenderManager.die();

    m_gameObjects.die();
  }
}