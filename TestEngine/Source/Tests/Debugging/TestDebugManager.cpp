#include "stdafx.h"

#include "Debugging/DebugManager.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"

#include <chrono>
#include <thread>

using namespace Kernel;
using namespace OpenGL;

namespace TestEngine
{
  static Path logFilePath(Directory::getExecutingAppDirectory());
  static Path resultsFilePath(Directory::getExecutingAppDirectory());
  static StringId codeBlockStringId = internString("Profile Code Block");

  TEST_CLASS(TestDebugManager), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestDebugManager_Initialize)
    {
      logFilePath.combine("Log.txt");
      resultsFilePath.combine("Profiling.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestDebugManager_MethodCleanup)
    {
      // Clear the log - naively at the moment by just attaching a new logger
      // TODO: Change this when we implent Logger::clear();
      DebugManager::setLogger(new ErrorLogger());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DebugManager_PROFILING_BLOCK_Macros)
    {
      int expectedTime = 1;

      BEGIN_PROFILING_BLOCK(codeBlockStringId);

      // Simulate some work
      std::this_thread::sleep_for(std::chrono::seconds(expectedTime));

      END_PROFILING_BLOCK(codeBlockStringId);

      const ProfilingBlock* profilingBlock = DebugManager::getProfiler()->getProfilingBlock(codeBlockStringId);

      Assert::IsNotNull(profilingBlock);
      Assert::AreEqual(1, profilingBlock->getNumCalls());
      AssertExt::assertAreAlmostEqual(expectedTime, profilingBlock->getAverageTimeTaken(), 0.5f);
      AssertExt::assertAreAlmostEqual(expectedTime, profilingBlock->getLastCallTimeTaken(), 0.5f);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_TestDebugManager_LOG_Macro)
    {
      std::string message("Test");
      
      LOG(message);

      DebugManager::getLogger()->flush();
      Assert::AreEqual(message + "\n", DebugManager::getLogger()->getLog());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LOG_WARNING_Macro)
    {
      std::string message("Message");

      int line = __LINE__; line++;
      LOG_WARNING(message);

      std::string expected("Warning: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LOG_WARNING_Macro, in file: testdebugmanager.cpp, on line: ");
      expected.append(std::to_string(line));
      expected.append("\n");

      DebugManager::getLogger()->flush();
      Assert::AreEqual(expected, DebugManager::getLogger()->getLog());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LOG_ERROR_Macro)
    {
      std::string message("Message");

      int line = __LINE__; line++;
      LOG_ERROR(message);

      std::string expected("Error: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LOG_ERROR_Macro, in file: testdebugmanager.cpp, on line: ");
      expected.append(std::to_string(line));
      expected.append("\n");

      DebugManager::getLogger()->flush();
      Assert::AreEqual(expected, DebugManager::getLogger()->getLog());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ErrorLogger_LOG_CRITICAL_ERROR_Macro)
    {
      std::string message("Message");

      int line = __LINE__; line++;
      LOG_CRITICAL_ERROR(message);

      std::string expected("Critical Error: ");
      expected.append(message);
      expected.append(" in function: Test_ErrorLogger_LOG_CRITICAL_ERROR_Macro, in file: testdebugmanager.cpp, on line: ");
      expected.append(std::to_string(line));
      expected.append("\n");

      DebugManager::getLogger()->flush();
      Assert::AreEqual(expected, DebugManager::getLogger()->getLog());
    }
  };
}