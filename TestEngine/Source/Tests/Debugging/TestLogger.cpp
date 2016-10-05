#include "stdafx.h"

#include "Debugging/Logging/Logger.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"

// There is ambiguity in naming with the unit test logger here
// So we qualify with namespaces

using namespace Kernel;

namespace TestEngine
{
  static std::string logFilePath;

  TEST_CLASS(TestLogger)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestLogger_Initialize)
    {
      Directory::getExecutingAppDirectory(logFilePath);
      File::combinePaths(logFilePath, "Log.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Constructor_NoErrors)
    {
      // Sanity check to catch any errors in constructor
      Engine::Logger logger;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Simple)
    {
      std::string message("Simple Log");

      Engine::Logger logger;
      logger.log(message);
      logger.flush();

      Assert::AreEqual(message, logger.getLog());

      checkLogFile(message);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Warning_Mutiple)
    {
      std::string message("Simple Log");

      Engine::Logger logger;
      logger.log(message);
      logger.log(message);
      logger.log(message);

      logger.flush();

      Assert::AreEqual(message + message + message, logger.getLog());

      checkLogFile(message + message + message);
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
      logger.log(message);
      logger.log(message);

      // Logger will flush when writing this message
      logger.log(message);

      // The first two messages should now be back in the back buffer
      Assert::AreEqual(message + message, logger.getLog());

      checkLogFile(message + message);
    }

    //------------------------------------------------------------------------------------------------
    void checkLogFile(const std::string& logFileContents)
    {
      std::string fileContents;
      File::readFile(logFilePath, fileContents);

      Assert::AreEqual(fileContents, logFileContents);
    }
  };
}