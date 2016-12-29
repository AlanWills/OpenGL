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

    m_renderManager.initialize();

    Handle<GameObject> gameObject = m_gameObjects.allocateAndInitialize();
    
    Handle<SpriteRenderer> spriteRenderer = gameObject->addComponent(SpriteRenderer::allocateWorldAndInitialize());
    spriteRenderer->setTexture("Fiirkan");
    spriteRenderer->setTransform(&gameObject->getTransform());

    Handle<TextRenderer> textRenderer = gameObject->addComponent(TextRenderer::allocateWorldAndInitialize());
    textRenderer->setText("World");

    Handle<GameObject> gameObject2 = m_gameObjects.allocateAndInitialize();

    Handle<SpriteRenderer> spriteRenderer2 = gameObject2->addComponent(SpriteRenderer::allocateScreenAndInitialize());
    spriteRenderer2->setTexture("ButtonDefault");
    spriteRenderer2->setTransform(&gameObject2->getTransform());

    Handle<TextRenderer> textRenderer2 = gameObject2->addComponent(TextRenderer::allocateScreenAndInitialize());
    textRenderer2->setText("Screen");

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

    m_renderManager.awake();
    m_gameObjects.awake();
  }

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_renderManager.handleInput(elapsedGameTime);
    m_gameObjects.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_renderManager.update(secondsPerUpdate);
    m_gameObjects.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::render(GLfloat lag)
  {
    Inherited::render(lag);

    m_renderManager.render(lag);
    m_gameObjects.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::die()
  {
    Inherited::die();

    m_renderManager.die();
    m_gameObjects.die();
  }
}