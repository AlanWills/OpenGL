#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());
  static StringId spriteStringId = internString("sprite");

  TEST_CLASS(TestResourceManager), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestResourceManager_Setup)
    {
      Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
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
      Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "", spriteStringId);
      Assert::IsNotNull(shader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetShader)
    {
      Shader* expectedShader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "", spriteStringId);
      Shader* actualShader = ResourceManager::getShader(spriteStringId);

      Assert::AreEqual(expectedShader, actualShader);
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

//----------------------------------------------------------------------------------------------------------
// Implementation of ToString for allocate result so that we can use Assert::AreEqual on AllocateResult enum
namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {

      template<>
      static std::wstring ToString<Shader>(Shader* shader)
      {
        return StringUtils::intToWchar((int)shader, 16);
      }
    }
  }
}