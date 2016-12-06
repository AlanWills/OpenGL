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

    for (SpriteRenderer* renderer : m_spriteRenderers)
    {

    }

    // Finish with our shader
    m_shader->unbind();
  }
}