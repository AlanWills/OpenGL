#include "stdafx.h"

#include "Debugging/Logging/Logger.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Logger::Logger() :
    m_verbosity(kAll),
    m_shouldFlushAfterEveryLog(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  Logger::~Logger()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Logger::log(const std::string& message, Verbosity verbosity)
  {
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
  }
}