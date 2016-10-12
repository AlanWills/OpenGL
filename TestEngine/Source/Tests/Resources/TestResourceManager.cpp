#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());

  TEST_CLASS(TestResourceManager)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestResourceManager_Setup)
    {
      Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResourceManager");
      testResourceDir = Directory(resourceDirPath);
      Assert::IsTrue(testResourceDir.exists());

      // This should allow us to change the resource manager to look for assets in our test directory
      ResourceManager::setResourceDirectoryPath(resourceDirPath);
      ResourceManager::init();
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
      Assert::Fail();
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