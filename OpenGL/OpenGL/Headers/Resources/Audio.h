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

    ALuint getBuffer() const { return m_buffer; }

  private:
    ALuint m_buffer;
};

}