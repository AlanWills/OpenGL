#include "stdafx.h"

#include "Debugging/Logging/Logger.h"
#include "FileSystem/Path.h"
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
      Path::combine(logFilePath, "Log.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Constructor_NoErrors)
    {
      // Sanity check to catch any errors in constructor and make sure the log file is cleared
      Engine::Logger logger;

      checkLogFile("");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Log_Simple)
    {
      std::string message("Simple Log");

      Engine::Logger logger;
      logger.log(message);
      logger.flush();

      Assert::AreEqual(message + "\n", logger.getLog());

      checkLogFile(message + "\n");
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

      Assert::AreEqual(message + "\n" + message + "\n" + message + "\n", logger.getLog());

      checkLogFile(message + "\n" + message + "\n" + message + "\n");
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
      Assert::AreEqual(message + "\n" + message + "\n", logger.getLog());

      checkLogFile(message + "\n" + message + "\n");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Logger_Destructor_WritesBothBuffersToFile)
    {
      std::string expected("Test");

      // Scope the logger so it is destroyed in this test rather than at the end
      {
        Engine::Logger logger;
        logger.log(expected);
      }

      checkLogFile(expected + "\n");
    }

    //------------------------------------------------------------------------------------------------
    void checkLogFile(const std::string& logFileContents)
    {
      AssertExt::assertFileContents(logFilePath, logFileContents);
    }
  };
}