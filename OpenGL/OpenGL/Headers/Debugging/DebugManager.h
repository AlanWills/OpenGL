#pragma once

#include "Logging/ErrorLogger.h"
#include "Profiling/Profiler.h"

#include <memory>

namespace OpenGL
{

#ifdef _DEBUG
#define BEGIN_PROFILING_BLOCK(name) Engine::DebugManager::getProfiler()->beginProfilingBlock(name);
#else
#define BEGIN_PROFILING(name)
#endif

#ifdef _DEBUG
#define END_PROFILING_BLOCK(name) Engine::DebugManager::getProfiler()->endProfilingBlock(name);
#else
#define END_PROFILING_BLOCK(name)
#endif

#ifdef _DEBUG
#define LOG(message) Engine::DebugManager::getLogger()->log(message);
#else
#define LOG(message)
#endif

#ifdef _DEBUG
#define BASIC_LOG_ERROR(message, verbosity) static_cast<Engine::ErrorLogger*>(Engine::DebugManager::getLogger())->logError(message, verbosity, FUNCTION, FILENAME, LINE);
#else
#define BASIC_LOG_ERROR(message, verbosity)
#endif

#ifdef _DEBUG
#define LOG_WARNING(message) BASIC_LOG_ERROR(message, Engine::ErrorLogger::Verbosity::kWarning)
#else
#define LOG_WARNING(message)
#endif

#ifdef _DEBUG
#define LOG_ERROR(message) BASIC_LOG_ERROR(message, Engine::ErrorLogger::Verbosity::kError)
#else
#define LOG_ERROR(message)
#endif

#ifdef _DEBUG
#define LOG_CRITICAL_ERROR(message) BASIC_LOG_ERROR(message, Engine::ErrorLogger::Verbosity::kCriticalError)
#else
#define LOG_CRITICAL_ERROR(message)
#endif

// A static class that is used to group various debugging tools together using the service locator pattern
// Contains: logger, profiler
class DebugManager
{
  public:
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