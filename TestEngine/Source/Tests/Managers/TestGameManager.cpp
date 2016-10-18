#include "stdafx.h"

#include "Managers/GameManager.h"
#include "Resources/ResourceManager.h"
#include "FileSystem/Directory.h"

using namespace Engine;

namespace TestEngine
{
  TEST_CLASS(TestGameManager)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_GameManager_Init)
    {
      Path path(Directory::getExecutingAppDirectory(), "..");
      path.combine("OpenGL");

      ResourceManager* resourceManager = new ResourceManager(path.asString());
      GameManager::setResourceManager(resourceManager);
      GameManager::init();

      Assert::IsNotNull(GameManager::getWindow());
      Assert::IsNotNull(GameManager::getResourceManager());
      Assert::IsNotNull(GameManager::getInputManager());
      Assert::IsNotNull(GameManager::getGameClock());
    }
  };
}