#include "stdafx.h"

#include "Debugging/Logging/ErrorLogger.h"

#include <string>

namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ErrorLogger::ErrorLogger(const std::string& logFileRelativePath) :
    Logger(logFileRelativePath),
    m_verbosity(kWarning | kError | kCriticalError)
  {
  }

  //------------------------------------------------------------------------------------------------
  ErrorLogger::~ErrorLogger()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ErrorLogger::logError(
    const std::string& message, 
    Verbosity verbosity,
    const char* function,
    const char* file,
    int line)
  {
    // If we have not indicated that the logger should log messages of the inputted verbosity
    // Then we do not log the message
    if (m_verbosity & verbosity == 0)
    {
      return;
    }

    std::string fullMessage;
    fullMessage.reserve(1024);

    fullMessage.append(getVerbosityString(verbosity));
    fullMessage.append(": ");
    fullMessage.append(message);
    fullMessage.append(" in function: ");
    fullMessage.append(function);
    fullMessage.append(", in file: ");
    fullMessage.append(file);
    fullMessage.append(", on line: ");
    fullMessage.append(std::to_string(line));

    log(fullMessage);
  }

  //------------------------------------------------------------------------------------------------
  const char* ErrorLogger::getVerbosityString(Verbosity verbosity)
  {
    switch (verbosity)
    {
      case kWarning:
        return WARNING_STRING;

      case kError:
        return ERROR_STRING;

      case kCriticalError:
        return CRITICAL_ERROR_STRING;

      default:
        ASSERT_FAIL();
        return "";
    }
  }
}