#pragma once

#include "DllExport.h"
#include "Memory/DoubleBufferAllocator.h"

namespace Engine
{

// A class used to log debug information
// Also writes to a file when it's buffer becomes too large
class DllExport Logger
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

    /// \brief Log the inputted message to the log buffer
    /// Will write to the log file if the buffer needs to be flushed
    void log(const std::string& message, Verbosity verbosity);

    /// \brief By default the logger buffers messages into bacthes before logging
    /// However, if we wish to log every message immediately then set this to true
    /// Be wary of using this in performance sensitive code
    void shouldFlushAfterEveryLog(bool shouldFlushAfterEveryLog) { m_shouldFlushAfterEveryLog = shouldFlushAfterEveryLog; }

    Logger();
    ~Logger();

  private:
    // The memory we will write to and use to write to the log file
    DoubleBufferAllocator<char, 2048> m_logBuffer;
    Verbosity m_verbosity;

    bool m_shouldFlushAfterEveryLog;
};

};