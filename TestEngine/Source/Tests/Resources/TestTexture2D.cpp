#include "stdafx.h"

#include "Resources/ResourceManager.h"
#include "Resources/Texture2D.h"

#include <SOIL/SOIL.h>

using namespace OpenGL;


namespace TestEngine
{
  static Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
  static StringId textureStringId = internString("texture");
  
  TEST_CLASS(TestTexture2D), public GLUnitTest
  {
  public:

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Texture2D_Generate)
    {
      Path texturePath(resourceDirPath);
      texturePath.combine("Assets").combine("block.png");

      Texture2D texture;

      int width, height;
      unsigned char* image = SOIL_load_image(texturePath.as_string().c_str(), &width, &height, 0, GL_FALSE);
      texture.generate(1, 1, image);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Texture2D_Bind)
    {
      ResourceManager resourceManager(resourceDirPath.as_string());

      Texture2D* texture = resourceManager.loadTexture("block.png", GL_TRUE, textureStringId);
      Assert::IsNotNull(texture);

      texture->bind();
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