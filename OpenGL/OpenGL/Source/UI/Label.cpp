#include "stdafx.h"

#include "UI/Label.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Label::Label() :
    m_textRenderer()
  {
  }

  //------------------------------------------------------------------------------------------------
  Label::~Label()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Label::initialize(const Handle<Component>&allocHandle)
  {
    Inherited::initialize(allocHandle);

    ADD_AND_INITIALIZE_CLASS_COMPONENT(TextRenderer, m_textRenderer);
  }

  //------------------------------------------------------------------------------------------------
  void Label::render(GLfloat lag)
  {
    // Unbind the sprite shader
    Handle<Shader> spriteShader = GameManager::getResourceManager()->loadShader("sprite.vert", "sprite.frag");
    spriteShader->unbind();

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();

    Handle<Shader> textShader = GameManager::getResourceManager()->loadShader("text.vert", "text.frag");

    textShader->bind();
    textShader->setMatrix4("projection", camera->getOrthographicProjectionMatrix());
    textShader->setMatrix4("view", glm::mat4());

    m_textRenderer.render(lag);

    // Finish with the text shader
    textShader->unbind();

    // Rebind the sprite shader
    spriteShader->bind();
  }
}