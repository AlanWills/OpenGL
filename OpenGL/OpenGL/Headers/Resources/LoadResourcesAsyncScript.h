#pragma once

#include "Scripts/Script.h"
#include <thread>


namespace OpenGL
{

class LoadResourcesAsyncScript : public Script
{
  #define MIN_WAIT_TIME 2

  DECLARE_COMPONENT(GapAllocator, LoadResourcesAsyncScript, 1);

  public:
    void awake() override;
    void update(GLfloat secondsPerUpdate) override;
    void die() override;

  private:
    typedef Script Inherited;

    float m_timeElapsed;

    // Don't like this, but running into copy constructor deletion issues
    // If there is a way around this, I'm all ears
    //std::thread* m_loadingThread;
};

}