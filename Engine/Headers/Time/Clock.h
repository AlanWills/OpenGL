#pragma once

#include "DllExport.h"
#include <cstdint>


namespace Engine
{

class DllExport Clock
{
  public:
    /// \brief This should be called before the clock class is used at the beginning of the program
    /// We have to pass in the cpuSpeed because apparently glfwGetTimerFrequency returns zero in this project
    static void init(uint64_t cpuSpeed);

    // Constructor & Destructor
    Clock(float startTimeSeconds = 0.0f);
    ~Clock();

    static uint64_t secondsToCycles(float timeSeconds);

    // WARNING: Dangerous - only use to convert small durations into seconds
    static float cyclesToSeconds(uint64_t timeCycles);

  private:
    static uint64_t s_cyclesPerSecond;

    uint64_t m_cycles;
    float m_timeScale;
    bool m_isPaused;
};

//------------------------------------------------------------------------------------------------
inline uint64_t Clock::secondsToCycles(float timeSeconds)
{
  return (uint64_t)(timeSeconds * s_cyclesPerSecond);
}

//------------------------------------------------------------------------------------------------
inline float Clock::cyclesToSeconds(uint64_t timeCycles)
{
  return (float)timeCycles / s_cyclesPerSecond;
}

// Initialize static variables
uint64_t Clock::s_cyclesPerSecond = 0;

};