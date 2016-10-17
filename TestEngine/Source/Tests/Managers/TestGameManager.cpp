#include "stdafx.h"

#include "Managers/GameManager.h"
#include "Resources/ResourceManager.h"
#include "FileSystem/Directory.h"

using namespace Engine;

namespace TestEngine
{
  static Path resourceManagerPath = ResourceManager::getResourceDirectoryPath();

  TEST_CLASS(TestGameManager)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestGameManager_ClassSetup)
    {
      Path path(Directory::getExecutingAppDirectory(), "..");
      path.combine("OpenGL");
      ResourceManager::setResourceDirectoryPath(path);
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestGameManager_ClassCleanup)
    {
      ResourceManager::setResourceDirectoryPath(resourceManagerPath);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_GameManager_Init)
    {
      GameManager::init();

      Assert::IsNotNull(GameManager::getWindow());
    }
  };
}