#pragma once

#include "Memory/DoubleBufferAllocator.h"

namespace OpenGL
{
#define LOGGER_BUFFER_SIZE 2048

// A class used to log information
// Also writes to a file when it's buffer becomes too large
// Any messages in the front buffer of the log are considered 'untouchable'
// If you wish to obtain them, call flush() and then call getLog() or read from the log file
class Logger
{
  public:
    /// \brief Pass in a custom path relative to the executing directory to specify the output log file
    Logger(const std::string& logRelativePath = "Log.txt");
    ~Logger();

    /// \brief Log the inputted message to the log buffer onto a new line
    /// Will write to the log file if the buffer needs to be flushed
    void log(const std::string& message);

    /// \brief Returns the string in the back log buffer
    const std::string& getLog();

    /// \brief Swaps the front log buffer with the back log buffer and writes the new back log buffer contents to the file
    /// Call when you have logged messages and you now wish to write them to file and then discard them
    void flush();

    /// \brief By default the logger buffers messages into batches before logging
    /// However, if we wish to log every message immediately then set this to true
    /// Be wary of using this in performance sensitive code
    void shouldFlushAfterEveryLog(bool shouldFlushAfterEveryLog) { m_shouldFlushAfterEveryLog = shouldFlushAfterEveryLog; }

  private:
    void writeLogBackBufferToFile();

    // The memory we will write to and use to write to the log file
    DoubleBufferAllocator<char, LOGGER_BUFFER_SIZE> m_logBuffer;

    std::string m_logFileFullPath;
    std::string m_backLogBufferStr;
    bool m_shouldFlushAfterEveryLog;
};

};