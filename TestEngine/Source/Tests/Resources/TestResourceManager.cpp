#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());
  static StringId spriteStringId = internString("sprite");

  TEST_CLASS(TestResourceManager)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestResourceManager_Setup)
    {
      GLFW_INIT();

      Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
      testResourceDir = Directory(resourceDirPath);
      Assert::IsTrue(testResourceDir.exists());

      // This should allow us to change the resource manager to look for assets in our test directory
      //ResourceManager::setResourceDirectoryPath(resourceDirPath);
      ResourceManager::init();
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestResourceManager_Cleanup)
    {
      GLFW_TERMINATE();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_CollectAllAssetsOnInit)
    {
      // Can use the directory getFiles stuff here to compare all asset types with those registered in ResourceManager
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadShader)
    {
      Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "", spriteStringId);
      Assert::IsNotNull(shader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetShader)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadTexture)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetTexture)
    {
      Assert::Fail();
    }

    // Then test the setters for the directories?  Is this necessary?  How do we actually get the Paths?
  };
}