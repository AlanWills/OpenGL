#include "stdafx.h"

#include "Rendering/RenderManager.h"
#include "Game/GameManager.h"
#include "Rendering/SpriteRenderer.h"


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
  void RenderManager::initialize()
  {
    Inherited::initialize();

    m_spriteShader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_spriteShader);
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

    // Finish with our shader
    m_spriteShader->unbind();
  }
}