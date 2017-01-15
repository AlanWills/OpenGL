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
    m_currentSecondsPerFrame(0),
    m_loop(true),
    m_playing(false)
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
    ASSERT(m_spriteRenderer.get());

    if (!m_frames.empty())
    {
      m_spriteRenderer->setTexture(m_frames.front());
    }
    else
    {
      // Shouldn't have an animation controller with no frames by this point
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void AnimationController::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    if (m_playing)
    {
      m_currentSecondsPerFrame += secondsPerUpdate;

      if (m_currentSecondsPerFrame > m_secondsPerFrame)
      {
        m_currentSecondsPerFrame -= m_secondsPerFrame;

        m_currentFrame++;
        m_currentFrame %= m_frames.size();

        m_spriteRenderer->setTexture(m_frames[m_currentFrame]);
        
        if (!m_loop && (m_currentFrame == m_frames.size() - 1))
        {
          // If we are not looping and we have reached the end of the animation frames we stop playing the animation
          // This will freeze the sprite renderer on the final frame
          m_playing = false;
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void AnimationController::resume()
  {
    if (m_loop || (m_currentFrame != m_frames.size() - 1))
    {
      // If we are looping or have not reached the end of a non-looping animation we continue playing
      m_playing = true;
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