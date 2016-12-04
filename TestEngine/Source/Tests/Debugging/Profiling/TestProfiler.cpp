#include "stdafx.h"

#include "Debugging/Profiling/Profiler.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"

#include <chrono>
#include <thread>

using namespace OpenGL;

namespace TestEngine
{
  static Path resultsFilePath(Directory::getExecutingAppDirectory());
  static StringId codeBlockStringId = internString("Profile Code Block");
  static StringId functionBlockStringId = internString("Profile Function Block");

  TEST_CLASS(TestProfiler)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestProfiler_Initialize)
    {
      // Set up glfw so we can get the time
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

      resultsFilePath.combine("Profiling.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Profiler_Constructor)
    {
      Profiler profiler;
      AssertExt::assertFileExists(resultsFilePath.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Profiler_ProfileCodeBlock)
    {
      Profiler profiler;
      int expectedTime = 1;

      profiler.beginProfilingBlock(codeBlockStringId);

      // Simulate some work
      std::this_thread::sleep_for(std::chrono::seconds(expectedTime));

      profiler.endProfilingBlock(codeBlockStringId);

      const ProfilingBlock* profilingBlock = profiler.getProfilingBlock(codeBlockStringId);

      Assert::IsNotNull(profilingBlock);
      Assert::AreEqual(1, profilingBlock->getNumCalls());
      AssertExt::assertAreAlmostEqual(expectedTime, profilingBlock->getAverageTimeTaken(), 0.5f);
      AssertExt::assertAreAlmostEqual(expectedTime, profilingBlock->getLastCallTimeTaken(), 0.5f);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Profiler_ProfileFunction)
    {
      Profiler profiler;
      int numCalls = 10;

      for (int i = 0; i < numCalls; ++i)
      {
        profiler.beginProfilingBlock(codeBlockStringId);

        testFunction();

        profiler.endProfilingBlock(codeBlockStringId);
      }

      const ProfilingBlock* profilingBlock = profiler.getProfilingBlock(codeBlockStringId);

      Assert::IsNotNull(profilingBlock);
      Assert::AreEqual(numCalls, profilingBlock->getNumCalls());
      AssertExt::assertAreAlmostEqual(0.1f, profilingBlock->getAverageTimeTaken(), 0.5f);
      AssertExt::assertAreAlmostEqual(0.1f, profilingBlock->getLastCallTimeTaken(), 0.5f);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Profiler_ProfileCodeBlock_FileResults)
    {
      int numCalls = 0;
      float averageTimeTaken = 0;
      float lastCallTimeTaken = 0;

      // Scope the profiler so that it is destroyed in this test and writes to the file
      {
        Profiler profiler;
        int expectedTime = 1;

        profiler.beginProfilingBlock(codeBlockStringId);

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::seconds(expectedTime));

        profiler.endProfilingBlock(codeBlockStringId);

        const ProfilingBlock* profilingBlock = profiler.getProfilingBlock(codeBlockStringId);
        Assert::IsNotNull(profilingBlock);

        numCalls = profilingBlock->getNumCalls();
        averageTimeTaken = profilingBlock->getAverageTimeTaken();
        lastCallTimeTaken = profilingBlock->getLastCallTimeTaken();
      }

      checkResultsFileContents(numCalls, averageTimeTaken, lastCallTimeTaken);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Profiler_ProfileFunction_FileResults)
    {
      int numCalls = 10;
      float averageTimeTaken = 0;
      float lastCallTimeTaken = 0;

      // Scope the profiler so that it is destroyed in this test and writes to the file
      {
        Profiler profiler;

        for (int i = 0; i < numCalls; ++i)
        {
          profiler.beginProfilingBlock(codeBlockStringId);

          testFunction();

          profiler.endProfilingBlock(codeBlockStringId);
        }

        const ProfilingBlock* profilingBlock = profiler.getProfilingBlock(codeBlockStringId);
        Assert::IsNotNull(profilingBlock);

        averageTimeTaken = profilingBlock->getAverageTimeTaken();
        lastCallTimeTaken = profilingBlock->getLastCallTimeTaken();
      }

      checkResultsFileContents(numCalls, averageTimeTaken, lastCallTimeTaken);
    }

    //------------------------------------------------------------------------------------------------
    void checkResultsFileContents(int numCalls, float averageTime, float lastTime)
    {
      std::string expectedFileContents;
      expectedFileContents.append("Profiling Block: ");
      expectedFileContents.append(deinternString(codeBlockStringId));
      expectedFileContents.append("\n");

      expectedFileContents.append("Number of calls: ");
      StringUtils::numericToStringAppend(numCalls, expectedFileContents);
      expectedFileContents.append("\n");

      expectedFileContents.append("Average time: ");
      StringUtils::numericToStringAppend(averageTime, expectedFileContents);
      expectedFileContents.append("\n");

      expectedFileContents.append("Last call time: ");
      StringUtils::numericToStringAppend(lastTime, expectedFileContents);
      expectedFileContents.append("\n");

      AssertExt::assertFileContents(resultsFilePath.asString(), expectedFileContents);
    }

    //------------------------------------------------------------------------------------------------
    void testFunction()
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  };
}