#pragma once

#include "Logger.h"

namespace Engine
{

// A class which not only provides message logging, but also logging of errors
// A message can be logged with a verbosity, which will also be recorded in the log
// The error logger can also filter certain errors and not record them if set appropriately
class DllExport ErrorLogger : public Logger
{
  public:
    enum Verbosity
    {
      kWarning = 1 << 0,  // Warnings are failures that should be fixed but the game can still run
      kError = 1 << 1,    // Errors constitute more serious problems that should be fixed immediately - the game may or may not be able to continue running
      kCriticalError = 1 << 2,  // Critical errors correspond to crashes
      kErrorsOnly = kCriticalError | kError,
      kAll = kCriticalError | kError | kWarning,
    };

    ErrorLogger(const std::string& logFileRelativePath = "ErrorLog.txt");
    ~ErrorLogger();

    /// \brief Custom logging function which also records the error warning level
    /// If the log is set to ignore errors of the inputted verbosity, this error will instead be dismissed
    void logError(const std::string& message, Verbosity verbosity);

  private:
    Verbosity m_verbosity;
};

};