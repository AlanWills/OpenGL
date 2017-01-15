#include "stdafx.h"

#include "Animation/AnimationController.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(AnimationController);

  //------------------------------------------------------------------------------------------------
  AnimationController::AnimationController() : 
    m_currentFrame(0),
    m_secondsPerFrame(0.1f),
    m_currentSecondsPerFrame(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  AnimationController::~AnimationController()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AnimationController::awake()
  {
    Inherited::awake();

    // This controller alters the attached sprite renderer's texture at regular intervals
    m_spriteRenderer = getParent()->findComponent<SpriteRenderer>();
  }

  //------------------------------------------------------------------------------------------------
  void AnimationController::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_currentSecondsPerFrame += secondsPerUpdate;

    if (m_currentSecondsPerFrame > m_secondsPerFrame)
    {
      m_currentSecondsPerFrame -= m_secondsPerFrame;

      m_currentFrame++;
      m_currentFrame %= m_frames.size();

      m_spriteRenderer->setTexture(m_frames[m_currentFrame]);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AnimationController::addFrame(const std::string& textureRelativePath)
  {
    // For safety's sake we shouldn't add frames after the initialization step
    // This is because we could be adding frames whilst altering the current frame
    // Similar to the adding objects whist iterating over a list problem we have all the time
    ASSERT(!isAwake());

    Handle<Texture2D> texture = GameManager::getResourceManager()->loadTexture(textureRelativePath);
    ASSERT(texture.get());

    m_frames.push_back(texture);
  }
}