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
    ASSERT(m_spriteShader);

    m_textShader = GameManager::getResourceManager()->getShader(s_textShaderId);
    ASSERT(m_textShader);
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

    for (SpriteRenderer* renderer : SpriteRenderer::m_componentAllocator)
    {
      renderer->render(lag);
    }

    // Finish with our sprite shader
    m_spriteShader->unbind();

    // Set up the text shader
    m_textShader->bind();

    m_textShader->setMatrix4("projection", 
      glm::ortho(0.0f, GameManager::getScreenManager()->getViewportWidth(), 0.0f, GameManager::getScreenManager()->getViewportHeight()));

    for (TextRenderer* renderer : TextRenderer::m_componentAllocator)
    {
      renderer->render(lag);
    }

    // Finish with the text shader
    m_textShader->unbind();
  }
}