#include "stdafx.h"

#include "Audio/AudioManager.h"
#include "Audio/AudioSource.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  AudioManager::AudioManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  AudioManager::~AudioManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    // Initialize alut in case it has not already
    ALboolean result = alutInit(nullptr, nullptr);
    ASSERT(result == AL_TRUE);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::awake()
  {
    Inherited::awake();

    AudioSource::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    AudioSource::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    AudioSource::m_componentAllocator.handleInput(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    AudioSource::m_componentAllocator.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::die()
  {
    Inherited::die();

    alutExit();
  }
}