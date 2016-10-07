#pragma once

#include "DllExport.h"
#include "Logging/ErrorLogger.h"
#include "Profiling/Profiler.h"

#include <memory>

namespace Engine
{

// A static class that is used to group various debugging tools together using the service locator pattern
// Contains: logger, profiler
class DllExport DebugManager
{
  public:
    /// \brief Set up a default logger and profiler
    static void init();

    /// \brief Set the logger to be used for debugging.  The DebugManager takes ownership and responsibility of the logger after using this function.
    static void setLogger(Logger* logger);
    static Logger* getLogger();

    /// \brief Set the profiler to be used for debugging.  The DebugManager takes ownership and responsibility of the profiler after using this function.
    static void setProfiler(Profiler* profiler);
    static Profiler* getProfiler();

  private:
    DebugManager();
    ~DebugManager();

    static std::unique_ptr<Logger> s_logger;
    static std::unique_ptr<Profiler> s_profiler;
};

}