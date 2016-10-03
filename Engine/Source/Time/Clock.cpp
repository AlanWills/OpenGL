#include "stdafx.h"

#include "Time/Clock.h"

namespace Engine
{
  // Initialize static variables
  uint64_t Clock::s_cyclesPerSecond = 0;

  //------------------------------------------------------------------------------------------------
  void Clock::init()
  {
    s_cyclesPerSecond = glfwGetTimerFrequency();
  }

  //------------------------------------------------------------------------------------------------
  Clock::Clock(float targetFramesPerSecond, float startTimeSeconds) :
    m_cycles(secondsToCycles(startTimeSeconds)),
    m_current(0),
    m_previous(0),
    m_timeScale(1.0f),  // Default to unscaled
    m_targetSecondsPerFrame(1.0f / targetFramesPerSecond),
    m_isPaused(false)   // Default to running
  {
  }

  //------------------------------------------------------------------------------------------------
  Clock::~Clock()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Clock::update()
  {
    if (!m_isPaused)
    {
      m_previous = m_current;
      m_current = glfwGetTime();
      m_cycles += secondsToCycles((m_current - m_previous) * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::singleStep()
  {
    if (!m_isPaused)
    {
      m_previous = m_current;
      m_current += m_targetSecondsPerFrame;

      // Add one target frame interval and scale by our current time scale
      m_cycles += secondsToCycles(m_targetSecondsPerFrame * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::reset()
  {
    m_cycles = 0;
    m_previous = 0;
    m_current = 0;
  }
}