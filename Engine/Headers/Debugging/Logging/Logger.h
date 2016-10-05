#pragma once

#include "DllExport.h"
#include "Memory/DoubleBufferAllocator.h"

namespace Engine
{
#define LOGGER_BUFFER_SIZE 2048

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

    /// \brief Pass in a custom path relative to the executing directory to specify the output log file
    Logger(const std::string& logRelativePath = "Log.txt");
    ~Logger();

    /// \brief Log the inputted message to the log buffer
    /// Will write to the log file if the buffer needs to be flushed
    void logMessage(const std::string& message, Verbosity verbosity);

    /// \brief Returns the string in the back log buffer
    const std::string& getBufferedLog();

    /// \brief Swaps the front log buffer with the back log buffer
    void flushBufferedLog() { m_logBuffer.swapBuffers(); }

    /// \brief By default the logger buffers messages into batches before logging
    /// However, if we wish to log every message immediately then set this to true
    /// Be wary of using this in performance sensitive code
    void shouldFlushAfterEveryLog(bool shouldFlushAfterEveryLog) { m_shouldFlushAfterEveryLog = shouldFlushAfterEveryLog; }

  private:
    // The memory we will write to and use to write to the log file
    DoubleBufferAllocator<char, LOGGER_BUFFER_SIZE> m_logBuffer;
    Verbosity m_verbosity;

    std::string m_logFileFullPath;
    std::string m_backLogBufferStr;
    bool m_shouldFlushAfterEveryLog;
};

};