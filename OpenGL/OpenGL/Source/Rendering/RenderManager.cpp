#include "stdafx.h"

#include "Game/GameManager.h"
#include "Rendering/RenderManager.h"


namespace OpenGL
{
  // Initialise static variables
  StringId RenderManager::s_spriteShaderId = internString("sprite");

  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager() :
    m_spriteShader(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  RenderManager::~RenderManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::init()
  {
    m_spriteShader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_spriteShader);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(GLfloat lag)
  {
    // Set up the sprite shader
    m_spriteShader->bind();

    Camera* camera = GameManager::getViewport()->getCamera();
    m_spriteShader->setMatrix4("projection", camera->getProjectionMatrix());
    m_spriteShader->setMatrix4("view", camera->getViewMatrix());

    for (SpriteRenderer* renderer : m_spriteRenderers)
    {
      renderer->render(lag);
    }

    // Finish with our shader
    m_spriteShader->unbind();
  }

  //------------------------------------------------------------------------------------------------
  SpriteRenderer* RenderManager::constructAndInitializeRenderer()
  {
    if (!m_spriteRenderers.canAllocate())
    {
      ASSERT_FAIL_MSG("Run out of renderers.  Consider increasing size");
      return nullptr;
    }
    
    return m_spriteRenderers.allocateAndInitialize();
  }
}