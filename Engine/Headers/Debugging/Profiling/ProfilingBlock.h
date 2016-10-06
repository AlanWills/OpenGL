#pragma once

#include "DllExport.h"

namespace Engine
{

/// A wrapper around some profiling information
/// Most of the implementation of this will be hidden except for a data access interface
class DllExport ProfilingBlock
{
  public:
    /// Hide the constructors and destructors
    ProfilingBlock() : m_averageTimeTaken(0), m_lastCallTimeTaken(0), m_numCalls(0), m_startTime(0) { }

    // TODO: Need to make the constructors private so this class can't be constructed except with the Profiler
    
    /// Getters for data - no public setters though (we want this class to be only be useful through using the Profiler)
    int getAverageTimeTaken() const { return m_averageTimeTaken; }
    int getLastCallTimeTaken() const { return m_lastCallTimeTaken; }
    int getNumCalls() const { return m_numCalls; }
    int getStartTime() const { return m_startTime; }

  private:
    /// An average of the time taken to run the block
    int m_averageTimeTaken;

    /// The time taken for the last call
    int m_lastCallTimeTaken;

    /// The number of times this profiling block has been entered
    int m_numCalls;

    /// The amount of time elapsed over the current call
    int m_startTime;

    friend class Profiler;
};

};