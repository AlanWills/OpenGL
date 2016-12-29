#include "stdafx.h"

#include "Rendering/RenderManager.h"
#include "Game/GameManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{
  // Initialise static variables
  StringId RenderManager::s_spriteShaderId = internString("sprite");
  StringId RenderManager::s_textShaderId = internString("text");

  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager() :
    m_spriteShader(nullptr),
    m_textShader(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  RenderManager::~RenderManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::initialize()
  {
    Inherited::initialize();

    m_spriteShader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_spriteShader.get());

    m_textShader = GameManager::getResourceManager()->getShader(s_textShaderId);
    ASSERT(m_textShader.get());
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::awake()
  {
    Inherited::awake();

    m_spriteRenderers.awake();
    m_textRenderers.awake();
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_spriteRenderers.handleInput(elapsedGameTime);
    m_textRenderers.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_spriteRenderers.update(secondsPerUpdate);
    m_textRenderers.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    // Set up the sprite shader
    m_spriteShader->bind();

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();
    m_spriteShader->setMatrix4("projection", camera->getProjectionMatrix());
    m_spriteShader->setMatrix4("view", camera->getViewMatrix());

    m_spriteRenderers.render(lag);

    // Finish with our sprite shader
    m_spriteShader->unbind();

    // Set up the text shader
    m_textShader->bind();

    m_textShader->setMatrix4("projection", 
      glm::ortho(0.0f, GameManager::getScreenManager()->getViewportWidth(), 0.0f, GameManager::getScreenManager()->getViewportHeight()));
    m_spriteShader->setMatrix4("view", glm::mat4());

    m_textRenderers.render(lag);

    // Finish with the text shader
    m_textShader->unbind();
  }
}