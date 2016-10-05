#include "stdafx.h"

#include "Debugging/Logging/ErrorLogger.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  ErrorLogger::ErrorLogger(const std::string& logFileRelativePath) :
    m_verbosity(kAll)
  {
  }

  //------------------------------------------------------------------------------------------------
  ErrorLogger::~ErrorLogger()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ErrorLogger::logError(const std::string& message, Verbosity verbosity)
  {
    // If we have not indicated that the logger should log messages of the inputted verbosity
    // Then we do not log the message
    if (m_verbosity & verbosity == 0)
    {
      return;
    }

    log(message);
  }
}