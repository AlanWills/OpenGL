#include "stdafx.h"

#include "Resources/ResourceManager.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"

using namespace Engine;


namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());
  static StringId shaderStringId = internString("sprite");

  TEST_CLASS(TestShader), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestResourceManager_ClassSetup)
    {
      Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
      testResourceDir = Directory(resourceDirPath);
      Assert::IsTrue(testResourceDir.exists());

      ResourceManager::setResourceDirectoryPath(testResourceDir.getDirectoryPath());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Shader_Compile)
    {
      std::string vertexShaderCode, fragmentShaderCode;
      Path vertexPath(testResourceDir.getDirectoryPath(), "Shaders");
      vertexPath.combine("Vertex").combine("sprite.vs");

      Path fragmentPath(testResourceDir.getDirectoryPath(), "Shaders");
      fragmentPath.combine("Fragment").combine("sprite.frag");

      File::read(vertexPath.asString(), vertexShaderCode);
      File::read(fragmentPath.asString(), fragmentShaderCode);

      Shader shader;
      shader.compile(vertexShaderCode, fragmentShaderCode);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Shader_Use)
    {
      Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", shaderStringId);
      Assert::IsNotNull(shader);

      shader->use();
    }
  };
}

//----------------------------------------------------------------------------------------------------------
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