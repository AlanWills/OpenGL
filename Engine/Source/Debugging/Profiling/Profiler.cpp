#include "stdafx.h"

#include "Debugging/Profiling/Profiler.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Profiler::Profiler(const std::string& profilingLogFileRelativePath) :
    m_logger(profilingLogFileRelativePath)
  {
  }

  //------------------------------------------------------------------------------------------------
  Profiler::~Profiler()
  {
  }
}