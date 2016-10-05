#include "stdafx.h"

#include "Debugging/Profiling/Profiler.h"
#include "StringInterning/StringId.h"

using namespace Kernel;

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