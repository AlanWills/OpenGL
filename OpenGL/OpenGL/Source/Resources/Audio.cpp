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
    ASSERT(File::exists(wavFileFullPath));
    m_buffer = alutCreateBufferFromFile((ALbyte*)wavFileFullPath.c_str());
  }
}