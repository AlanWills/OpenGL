#include "stdafx.h"

#include "UI/UIManager.h"
#include "UI/Button.h"
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
  void UIManager::initialize()
  {
    Inherited::initialize();

    m_spriteShader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_spriteShader.get());

    m_textShader = GameManager::getResourceManager()->getShader(s_textShaderId);
    ASSERT(m_textShader.get());
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::awake()
  {
    Inherited::awake();

    Button::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    Button::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    Button::m_componentAllocator.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();

    // Render world space sprites
    {
      m_spriteShader->bind();
      m_spriteShader->setMatrix4("projection", camera->getOrthographicProjectionMatrix());
      m_spriteShader->setMatrix4("view", glm::mat4());

      Button::m_componentAllocator.render(lag);

      m_spriteShader->unbind();
    }

    // Render world space text
    //{
    //  m_textShader->bind();
    //  m_textShader->setMatrix4("projection",
    //    glm::perspective(45.0f, GameManager::getScreenManager()->getViewportWidth() / GameManager::getScreenManager()->getViewportHeight(), 0.1f, 100.0f));
    //  m_textShader->setMatrix4("view", camera->getViewMatrix());

    //  TextRenderer::m_componentAllocator.render(lag);

    //  // Finish with the text shader
    //  m_textShader->unbind();
    //}
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::die()
  {
    Inherited::die();

    Button::m_componentAllocator.die();
  }
}