#pragma once

#include "DllExport.h"
#include <cstdint>


namespace Engine
{

#define DEFAULT_TARGET_FPS 50

class DllExport Clock
{
  public:
    /// \brief This should be called before the clock class is used at the beginning of the program
    /// We have to pass in the cpuSpeed because apparently glfwGetTimerFrequency returns zero in this project
    static void init(uint64_t cpuSpeed);

    // Constructor & Destructor
    Clock(float targetFramesPerSecond = DEFAULT_TARGET_FPS, float startTimeSeconds = 0.0f);
    ~Clock();

    static uint64_t secondsToCycles(float timeSeconds);

    // WARNING: Dangerous - only use to convert small durations into seconds
    static float cyclesToSeconds(uint64_t timeCycles);

    /// \brief This function should be called once per frame with the real measured frame time delta in seconds.
    void update(float elapsedGameTime);

    /// \brief Advance the clock by the time scale dictated by our desired FPS
    void singleStep();

    /// \brief Determine the difference between this clock's absolute time and that of another clock in seconds.
    /// We only return time deltas as floats, due to the limited precision of a 32-bit float.
    float calculateDeltaSeconds(const Clock& otherClock) const;

    /// \brief Reset the clock cycles counter to zero
    void reset() { m_cycles = 0; }

    /// \brief Return the total cycles since the last reset rather than the time in seconds
    /// as a float does not have enough accuracy
    uint64_t getElapsedCycles() const { return m_cycles; }

    void setTimeScale(float timeScale) { m_timeScale = timeScale; }
    float getTimeScale() const { return m_timeScale; }

    void setTargetFramesPerSecond(int framesPerSecond) { m_targetSecondsPerFrame = (1.0f / framesPerSecond); }
    int getTargetFramesPerSecond() const { return (int)1 / m_targetSecondsPerFrame; }

    void setPaused(bool isPaused) { m_isPaused = isPaused; }
    bool getPaused() const { return m_isPaused; }

  private:
    static uint64_t s_cyclesPerSecond;

    uint64_t m_cycles;
    float m_timeScale;
    float m_targetSecondsPerFrame;
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

};