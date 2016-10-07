#pragma once

#include "Logger.h"
#include "FileSystem/Path.h"

#include <string.h>

namespace Engine
{
#define FUNCTION __func__
#define FILENAME (strrchr(__FILE__, PATH_DELIMITER) ? strrchr(__FILE__, PATH_DELIMITER) + 1 : __FILE__)
#define LINE __LINE__

#define WARNING_STRING "Warning"
#define ERROR_STRING "Error"
#define CRITICAL_ERROR_STRING "Critical Error"

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
    };

    ErrorLogger(const std::string& logFileRelativePath = "ErrorLog.txt");
    ~ErrorLogger();

    /// \brief Custom logging function which also records the error warning level
    /// If the log is set to ignore errors of the inputted verbosity, this error will instead be dismissed
    /// Use the FUNCTION, FILENAME and LINE macros for the last three parameters
    void logError(const std::string& message, Verbosity verbosity, const char* function, const char* file, int line);

    /// \brief Obtain a string we will use to build our error logging based on the inputted verbosity
    static const char* getVerbosityString(Verbosity verbosity);

  private:
    int m_verbosity;
};

};