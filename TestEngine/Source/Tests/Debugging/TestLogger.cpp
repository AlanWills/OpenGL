#include "stdafx.h"

#include "Debugging/Logging/Logger.h"

// There is ambiguity in naming with the unit test logger here
// So we qualify with namespaces

namespace TestEngine
{
  TEST_CLASS(TestLogger)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Constructor_NoErrors)
    {
      // Sanity check to catch any errors in constructor
      Engine::Logger logger;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Warning_Simple)
    {
      std::string message("Simple Log");

      Engine::Logger logger;
      logger.logMessage(message, Engine::Logger::kWarning);
      logger.flushBufferedLog();

      Assert::AreEqual(message, logger.getBufferedLog());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Warning_Mutiple)
    {
      std::string message("Simple Log");

      Engine::Logger logger;
      logger.logMessage(message, Engine::Logger::kWarning);
      logger.logMessage(message, Engine::Logger::kWarning);
      logger.logMessage(message, Engine::Logger::kWarning);

      logger.flushBufferedLog();

      Assert::AreEqual(message + message + message, logger.getBufferedLog());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Warning_FlushDuringWriting)
    {
      std::string message;
      for (size_t i = 0; i < (size_t)(LOGGER_BUFFER_SIZE * 0.49f); ++i)
      {
        message.append("S");
      }

      Engine::Logger logger;
      logger.logMessage(message, Engine::Logger::kWarning);
      logger.logMessage(message, Engine::Logger::kWarning);

      // Logger will flush when writing this message
      logger.logMessage(message, Engine::Logger::kWarning);

      // The first two messages should now be back in the back buffer
      Assert::AreEqual(message + message, logger.getBufferedLog());
    }
  };
}