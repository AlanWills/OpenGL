#pragma once

#include "alut/alut.h"

#include <string>


namespace OpenGL
{

class Audio
{
  public:
    Audio();
    ~Audio();

    void generate(const std::string& wavFullFilePath);

  private:
    ALuint m_buffer;
};

}