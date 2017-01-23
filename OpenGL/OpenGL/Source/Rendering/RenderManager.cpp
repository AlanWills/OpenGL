#include "stdafx.h"

#include "Rendering/RenderManager.h"
#include "Game/GameManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager() :
    m_spriteShader(nullptr),
    m_textShader(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::initialize(const Handle<Component>& allocHandle)
  {
    Inherited::initialize(allocHandle);

    m_spriteShader = GameManager::getResourceManager()->loadShader("sprite.vert", "sprite.frag");
    ASSERT(m_spriteShader.get());

    m_textShader = GameManager::getResourceManager()->loadShader("text.vert", "text.frag");
    ASSERT(m_textShader.get());
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::awake()
  {
    Inherited::awake();

    SpriteRenderer::m_componentAllocator.awake();
    TextRenderer::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    SpriteRenderer::m_componentAllocator.handleInput(elapsedGameTime);
    TextRenderer::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    SpriteRenderer::m_componentAllocator.update(secondsPerUpdate);
    TextRenderer::m_componentAllocator.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();

    // Render world space sprites
    {
      m_spriteShader->bind();
      m_spriteShader->setMatrix4("projection", camera->getPerspectiveProjectionMatrix());
      m_spriteShader->setMatrix4("view", camera->getViewMatrix());

      SpriteRenderer::m_componentAllocator.render(lag);

      m_spriteShader->unbind();
    }

    // Render world space text
    {
      m_textShader->bind();
      m_textShader->setMatrix4("projection", 
        glm::perspective(45.0f, GameManager::getScreenManager()->getViewportWidth() / GameManager::getScreenManager()->getViewportHeight(), 0.1f, 100.0f));
      m_textShader->setMatrix4("view", camera->getViewMatrix());

      TextRenderer::m_componentAllocator.render(lag);

      // Finish with the text shader
      m_textShader->unbind();
    }
  }
}