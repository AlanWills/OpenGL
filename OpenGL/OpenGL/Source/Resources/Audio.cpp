#include "stdafx.h"

#include "Resources/Audio.h"
#include "FileSystem/File.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Audio::Audio() :
    m_buffer(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  Audio::~Audio()
  {
    alDeleteBuffers(1, &m_buffer);
  }

  //------------------------------------------------------------------------------------------------
  void Audio::generate(const std::string& wavFileFullPath)
  {
    // Initialize alut in case it has not already
    ALboolean result = alutInit(nullptr, nullptr);
    ASSERT(result == AL_TRUE);

    ASSERT(File::exists(wavFileFullPath));
    ALuint buffer = alutCreateBufferFromFile((ALbyte*)wavFileFullPath.c_str());
  }
}