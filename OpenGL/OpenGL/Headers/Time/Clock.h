#pragma once

#include <cstdint>
#include <ctime>


namespace OpenGL
{

#define DEFAULT_TARGET_FPS 50

class Clock
{
  public:
    // Constructor & Destructor
    Clock(float targetFramesPerSecond = DEFAULT_TARGET_FPS, float startTimeSeconds = 0);
    ~Clock();

    static uint64_t secondsToCycles(float timeSeconds);

    // WARNING: Dangerous - only use to convert small durations into seconds
    static float cyclesToSeconds(uint64_t timeCycles);

    /// \brief This function should be called once per frame with the real measured frame time delta in seconds.
    void update();

    /// \brief Advance the clock by the time scale dictated by our desired FPS
    void singleStep();

    /// \brief Reset the clock cycles counter to zero
    void reset();

    /// \brief Return the total cycles since the last reset rather than the time in seconds
    /// as a float does not have enough accuracy
    uint64_t getElapsedCycles() const { return m_cycles; }

    /// \brief Return the time since this clock was last updated
    GLfloat getElapsedDeltaTime() const { return (m_current - m_previous) * m_timeScale; }

    void setTimeScale(float timeScale) { m_timeScale = timeScale; }
    float getTimeScale() const { return m_timeScale; }

    void setTargetFramesPerSecond(int framesPerSecond) { m_targetSecondsPerFrame = (1.0f / framesPerSecond); }
    int getTargetFramesPerSecond() const { return (int)1 / m_targetSecondsPerFrame; }

    void setPaused(bool isPaused) { m_isPaused = isPaused; }
    bool getPaused() const { return m_isPaused; }

  private:
    uint64_t m_cycles;
    GLfloat m_current;
    GLfloat m_previous;
    float m_timeScale;
    float m_targetSecondsPerFrame;
    bool m_isPaused;
};

//------------------------------------------------------------------------------------------------
inline uint64_t Clock::secondsToCycles(float timeSeconds)
{
  return (uint64_t)(timeSeconds * CLOCKS_PER_SEC);
}

//------------------------------------------------------------------------------------------------
inline float Clock::cyclesToSeconds(uint64_t timeCycles)
{
  return (float)timeCycles / CLOCKS_PER_SEC;
}

};