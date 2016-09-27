#include "stdafx.h"

#include "Time/Clock.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  void Clock::init(uint64_t cpuSpeed)
  {
    s_cyclesPerSecond = cpuSpeed;
  }

  //------------------------------------------------------------------------------------------------
  Clock::Clock(float startTimeSeconds) :
    m_cycles(secondsToCycles(startTimeSeconds)),
    m_timeScale(1.0f),  // Default to unscaled
    m_isPaused(false)   // Default to running
  {
  }

  //------------------------------------------------------------------------------------------------
  Clock::~Clock()
  {
  }
}