#include "stdafx.h"

#include "Game/GameManager.h"
#include "Rendering/RenderManager.h"


namespace OpenGL
{
  // Initialise static variables
  StringId RenderManager::s_spriteShaderId = internString("sprite");

  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager() :
    m_shader(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  RenderManager::~RenderManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::init()
  {
    m_shader = GameManager::getResourceManager()->getShader(s_spriteShaderId);
    ASSERT(m_shader);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(GLfloat lag)
  {
    // Set up the sprite shader
    m_shader->bind();

    Camera* camera = GameManager::getViewport()->getCamera();
    m_shader->setMatrix4("projection", camera->getProjectionMatrix());
    m_shader->setMatrix4("view", camera->getViewMatrix());

    for (SpriteRenderer* renderer : m_spriteRenderers)
    {
      renderer->render(lag, m_shader);
    }

    // Finish with our shader
    m_shader->unbind();
  }
}