#include "stdafx.h"

#include "Audio/AudioSource.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(AudioSource);

  //------------------------------------------------------------------------------------------------
  AudioSource::AudioSource() :
    m_audio(nullptr),
    m_source(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  AudioSource::~AudioSource()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);
    
    alGenSources(1, &m_source);
    alSourcef(m_source, AL_PITCH, 1);
    alSourcef(m_source, AL_GAIN, 1);
    alSource3f(m_source, AL_POSITION, 0, 0, 0);
    alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
    alSourcei(m_source, AL_LOOPING, AL_FALSE);
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::die()
  {
    Inherited::die();

    alDeleteSources(1, &m_source);
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setAudio(const std::string& wavFileRelativePath)
  {
    m_audio = GameManager::getResourceManager()->loadAudio(wavFileRelativePath);
    ASSERT(m_audio.get());

    alSourcei(m_source, AL_BUFFER, m_audio->getBuffer());
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setAudio(const Handle<Audio>& audio)
  {
    m_audio = audio;
    ASSERT(m_audio.get());

    alSourcei(m_source, AL_BUFFER, m_audio->getBuffer());
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::play() const
  {
    if (!m_audio.get())
    {
      ASSERT_FAIL();
    }
    
    alSourcePlay(m_source);
  }
}