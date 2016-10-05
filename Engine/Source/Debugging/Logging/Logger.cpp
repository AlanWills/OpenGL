#include "stdafx.h"

#include "Debugging/Logging/Logger.h"
#include "FileSystem/Directory.h"
#include "FileSystem/File.h"

#include <thread>

using namespace Kernel;

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Logger::Logger(const std::string& logRelativePath) :
    m_verbosity(kAll),
    m_shouldFlushAfterEveryLog(false)
  {
    m_backLogBufferStr.reserve(LOGGER_BUFFER_SIZE);
    m_backLogBufferStr.clear();

    Directory::getExecutingAppDirectory(m_logFileFullPath);
    File::combinePaths(m_logFileFullPath, logRelativePath);
    File::createFile(m_logFileFullPath);  // Clears the log file if it already exists
  }

  //------------------------------------------------------------------------------------------------
  Logger::~Logger()
  {
  }

  //------------------------------------------------------------------------------------------------
  /*void asyncWriteToLogFile(const std::string& logFileFullPath, const std::string& bufferedLog)
  {
    File::appendToFile(logFileFullPath, bufferedLog);
  }*/

  //------------------------------------------------------------------------------------------------
  void Logger::logMessage(const std::string& message, Verbosity verbosity)
  {
    // If we have not indicated that the logger should log messages of the inputted verbosity
    // Then we do not log the message
    if (m_verbosity & verbosity == 0)
    {
      return;
    }

    // Store the message into our buffer
    AllocateResult allocResult = m_logBuffer.copyAllocate(message.length(), message.c_str());

    if (allocResult == AllocateResult::kNoFlushRequired)
    {
      if (!m_shouldFlushAfterEveryLog)
      {
        // If we don't need to flush and we should flush after every log, we are done
        return;
      }

      // We didn't need to flush our buffers during the alloc, but we should be doing so after every log
      // Swapping the buffers will move the message we just wrote to the buffers to be moved to the back buffer
      m_logBuffer.swapBuffers();
    }
    
    // Since our log buffers have been flushed, we should write the contents of the back buffer to the log file
    // TODO: Make this async
    writeLogBackBufferToFile();
  }

  //------------------------------------------------------------------------------------------------
  void Logger::flush()
  {
    m_logBuffer.swapBuffers();

    writeLogBackBufferToFile();
  }

  //------------------------------------------------------------------------------------------------
  void Logger::writeLogBackBufferToFile()
  {
    File::appendToFile(m_logFileFullPath, getLog());
  }

  //------------------------------------------------------------------------------------------------
  const std::string& Logger::getLog()
  {
    m_backLogBufferStr.clear();

    const char* bufferedMessages = nullptr;
    m_logBuffer.getBufferedData(&bufferedMessages);

    m_backLogBufferStr.append(bufferedMessages);

    return m_backLogBufferStr;
  }
}