#pragma once

#include "StringInterning/StringId.h"
#include "Debugging/Logging/Logger.h"
#include "Memory/PoolAllocator.h"
#include "ProfilingBlock.h"

#include <unordered_map>


namespace OpenGL
{
// TODO: Profiling hierarchy so we do not get overlap in our profiling times

#define MAX_PROFILING_BLOCKS 100

// Times sections of code and records them in a database with appropriate information
// Also outputs results to a log file
class Profiler
{
  public:
    Profiler(const std::string& profilingFileRelativePath = "Profiling.txt");
    ~Profiler();

    /// \brief Begin a profiling block
    /// Will create a new block if one for the inputted profiling name does not exist
    void beginProfilingBlock(StringId profilingBlockName);

    /// \brief Close off the profiling block and check the input matches the current block running
    void endProfilingBlock(StringId profilingBlockName);

    /// \brief Return a profiling block corresponding to the inputted name to inspect the current profiling results
    /// Returns null if profiling block does not exist
    const ProfilingBlock* getProfilingBlock(StringId profilingBlockName);

  private:
    /// \brief Build our profiling information into a string and write it to our log
    void logProfilingBlockInfo(const std::pair<StringId, ProfilingBlock>& profilingInfo);

    /// \brief We allocate a load of memory for profiling blocks rather than creating them at runtime
    /// Since they will persist for the entirity of this object's lifespan it seemed like an allowable tradeoff
    /// In the end, we should move this to a debug section of memory
    PoolAllocator<ProfilingBlock, MAX_PROFILING_BLOCKS> m_profilingBlockPool;

    /// The map we will store profiling information in
    std::unordered_map<StringId, ProfilingBlock> m_profilingInfo;

    /// Not necessary, but useful for debugging to make people aware they have closed off profiling blocks incorrectly
    StringId m_currentBlockName;

    /// The logger we will use to write profiling information to a file
    Logger m_logger;
};

};