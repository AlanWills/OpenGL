#include "stdafx.h"

#include "Debugging/Logging/ErrorLogger.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"

// There is ambiguity in naming with the unit test logger here
// So we qualify with namespaces

using namespace Kernel;
using namespace Engine;

namespace TestEngine
{
  static std::string logFilePath;

  TEST_CLASS(TestErrorLogger)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestErrorLogger_Initialize)
    {
      Directory::getExecutingAppDirectory(logFilePath);
      File::combinePaths(logFilePath, "ErrorLog.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_Constructor_NoErrors)
    {
      // Sanity check to catch any errors in constructor
      ErrorLogger logger;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LogWarning)
    {
      std::string message("Message");

      // Sanity check to catch any errors in constructor
      ErrorLogger logger;
      int line = __LINE__; line++;
      logger.logError(message, ErrorLogger::kWarning, FUNCTION, FILENAME, LINE);
      logger.flush();

      std::string expected("Warning: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LogWarning, in file: testerrorlogger.cpp, on line: ");
      expected.append(std::to_string(line));

      Assert::AreEqual(expected, logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LogError)
    {
      std::string message("Message");

      // Sanity check to catch any errors in constructor
      ErrorLogger logger;
      int line = __LINE__; line++;
      logger.logError(message, ErrorLogger::kError, FUNCTION, FILENAME, LINE);
      logger.flush();

      std::string expected("Error: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LogError, in file: testerrorlogger.cpp, on line: ");
      expected.append(std::to_string(line));

      Assert::AreEqual(expected, logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LogCriticalError)
    {
      std::string message("Message");

      // Sanity check to catch any errors in constructor
      ErrorLogger logger;
      int line = __LINE__; line++;
      logger.logError(message, ErrorLogger::kCriticalError, FUNCTION, FILENAME, LINE);
      logger.flush();

      std::string expected("Critical Error: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LogCriticalError, in file: testerrorlogger.cpp, on line: ");
      expected.append(std::to_string(line));

      Assert::AreEqual(expected, logger.getLog());

      checkLogFile(expected);
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