#pragma once

#include "DllExport.h"

#include "Debugging/Logging/Logger.h"

namespace Engine
{

// Times sections of code and records them in a database
// Also outputs results to a log file
class DllExport Profiler
{
  public:
    Profiler(const std::string& profilingFileRelativePath = "Profiling.txt");
    ~Profiler();

  private:
    Logger m_logger;
};

};