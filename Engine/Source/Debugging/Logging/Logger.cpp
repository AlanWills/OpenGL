#include "stdafx.h"

#include "Debugging/Logging/Logger.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Logger::Logger() :
    m_verbosity(kAll)
  {
  }

  //------------------------------------------------------------------------------------------------
  Logger::~Logger()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Logger::log(const std::string& message, Verbosity verbosity)
  {
    m_logBuffer.copyAllocate(message.length(), message.c_str());
  }
}