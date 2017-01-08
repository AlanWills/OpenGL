#include "stdafx.h"

#include "UI/UIManager.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  // Initialise static variables
  StringId UIManager::s_spriteShaderId = internString("sprite");
  StringId UIManager::s_textShaderId = internString("text");

  //------------------------------------------------------------------------------------------------
  UIManager::UIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  UIManager::~UIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    m_spriteShader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_spriteShader.get());

    m_textShader = GameManager::getResourceManager()->getShader(s_textShaderId);
    ASSERT(m_textShader.get());
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::awake()
  {
    Inherited::awake();

    m_buttons.awake();
    m_images.awake();
    m_labels.awake();
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_buttons.handleInput(elapsedGameTime);
    m_images.handleInput(elapsedGameTime);
    m_labels.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_buttons.update(secondsPerUpdate);
    m_images.update(secondsPerUpdate);
    m_labels.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();

    // Render screen space sprites
    {
      m_spriteShader->bind();
      m_spriteShader->setMatrix4("projection", camera->getOrthographicProjectionMatrix());
      m_spriteShader->setMatrix4("view", glm::mat4());

      m_buttons.render(lag);
      m_images.render(lag);

      m_spriteShader->unbind();
    }

    // Render screen space text
    {
      m_labels.render(lag);
    }
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::die()
  {
    Inherited::die();

    m_buttons.die();
    m_images.die();
    m_labels.die();
  }
}