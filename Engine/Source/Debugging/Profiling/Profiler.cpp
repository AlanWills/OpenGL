#include "stdafx.h"

#include "Debugging/Profiling/Profiler.h"
#include "StringInterning/StringId.h"

using namespace Kernel;

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Profiler::Profiler(const std::string& profilingLogFileRelativePath) :
    m_logger(profilingLogFileRelativePath),
    m_currentBlockName(0)
  {
    // We have a fixed max size so we can just reserve our map size straightaway to avoid runtime allocations
    m_profilingInfo.reserve(MAX_PROFILING_BLOCKS);
  }

  //------------------------------------------------------------------------------------------------
  Profiler::~Profiler()
  {
    /// Write all information to log here
    for (const std::pair<StringId, ProfilingBlock>& pair : m_profilingInfo)
    {
      logProfilingBlockInfo(pair);
    }
    
    // When the logger is destroyed it will take care of flushing the front log buffer so we just need to log all the data
    // and it will take care of the rest
  }

  //------------------------------------------------------------------------------------------------
  void Profiler::logProfilingBlockInfo(const std::pair<StringId, ProfilingBlock>& profilingInfo)
  {
    // Write in chunks so we do not overflow the buffer

    std::string logString;
    logString.reserve(100);

    // Block name
    {
      logString.append("Profiling Block: ");
      logString.append(deinternString(profilingInfo.first));

      m_logger.log(logString);
      logString.clear();
    }

    // Num calls
    {
      logString.append("Number of calls: ");
      StringUtils::intToStringAppend(profilingInfo.second.m_numCalls, logString);

      m_logger.log(logString);
      logString.clear();
    }

    // Last call time
    {
      logString.append("Last call time: ");
      StringUtils::intToStringAppend(profilingInfo.second.m_lastCallTimeTaken, logString);

      m_logger.log(logString);
      logString.clear();
    }

    // Average time
    {
      logString.append("Average time: ");
      StringUtils::intToStringAppend(profilingInfo.second.m_averageTimeTaken, logString);

      m_logger.log(logString);
      logString.clear();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Profiler::startProfilingBlock(StringId profilingBlockName)
  {
    m_currentBlockName = profilingBlockName;

    // If we do not have a profiling block for the inputted name we must add one from our pool
    if (m_profilingInfo.find(profilingBlockName) == m_profilingInfo.end())
    {
      // TODO: Add one from pool
      ASSERT_FAIL();
    }

    ProfilingBlock& profilingBlock = m_profilingInfo[profilingBlockName];
    profilingBlock.m_startTime = glfwGetTime(); // Use realtime clock here?
  }

  //------------------------------------------------------------------------------------------------
  void Profiler::endProfilingBlock(StringId profilingBlockName)
  {
    ASSERT_MSG(profilingBlockName == m_currentBlockName, "Not closing the latest opened profiling block");
    ASSERT(m_profilingInfo.find(profilingBlockName) != m_profilingInfo.end());

    ProfilingBlock& profilingBlock = m_profilingInfo[profilingBlockName];

    float timeTaken = glfwGetTime() - profilingBlock.m_startTime;
    float averageTimeTake = profilingBlock.m_averageTimeTaken;
    int numCalls = profilingBlock.m_numCalls;

    // Update profiling data
    profilingBlock.m_lastCallTimeTaken = timeTaken;
    profilingBlock.m_averageTimeTaken = (averageTimeTake * numCalls + timeTaken) / (++numCalls);
    profilingBlock.m_numCalls = numCalls;
  }
}