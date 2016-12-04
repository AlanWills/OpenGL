#include "stdafx.h"

#include "DebugUtils/Debug.h"
#include "Debugging/DebugManager.h"

namespace OpenGL
{
  // Initialise the static members here
  std::unique_ptr<Profiler> DebugManager::s_profiler(new Profiler());
  std::unique_ptr<Logger> DebugManager::s_logger(new ErrorLogger());

  //------------------------------------------------------------------------------------------------
  DebugManager::DebugManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  DebugManager::~DebugManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void DebugManager::setLogger(Logger* logger)
  {
    ASSERT(logger);
    s_logger.reset(logger);
  }

  //------------------------------------------------------------------------------------------------
  Logger* DebugManager::getLogger()
  {
    ASSERT(s_logger.get());
    return s_logger.get();
  }

  //------------------------------------------------------------------------------------------------
  void DebugManager::setProfiler(Profiler* profiler)
  {
    ASSERT(profiler);
    s_profiler.reset(profiler);
  }

  //------------------------------------------------------------------------------------------------
  Profiler* DebugManager::getProfiler()
  {
    ASSERT(s_profiler.get());
    return s_profiler.get();
  }
};