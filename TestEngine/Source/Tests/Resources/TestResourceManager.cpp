#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());
  static StringId shaderStringId = internString("sprite");
  static StringId textureStringId = internString("texture");

  TEST_CLASS(TestResourceManager), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestResourceManager_ClassSetup)
    {
      Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
      testResourceDir = Directory(resourceDirPath);
      Assert::IsTrue(testResourceDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_INITIALIZE(TestResourceManager_Setup)
    {
      // This should allow us to change the resource manager to look for assets in our test directory
      ResourceManager::setResourceDirectoryPath(testResourceDir.getDirectoryPath());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestResourceManager_Cleanup)
    {
      // Unload the resources between each test to reset the resource manager
      ResourceManager::unloadAllAssets();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetResourceDirectoryPath)
    {
      Path original = ResourceManager::getResourceDirectoryPath();

      // Do the test
      {
        Path expected(Directory::getExecutingAppDirectory(), "Res");
        ResourceManager::setResourceDirectoryPath(expected);

        Assert::AreEqual(expected, ResourceManager::getResourceDirectoryPath());

        // Check shader and texture dirs have been updated
        {
          Path expectedText(expected.asString(), TEXTURE_DIR);
          Assert::AreEqual(expectedText, ResourceManager::getTextureDirectoryPath());
        }

        {
          Path expectedShad(expected.asString(), SHADER_DIR);
          Assert::AreEqual(expectedShad, ResourceManager::getShaderDirectoryPath());
        }
      }

      // Set it back to cleanup the test
      ResourceManager::setResourceDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetTextureDirectoryPath)
    {
      Path original = ResourceManager::getTextureDirectoryPath();

      // Do the test
      {
        Path expected(testResourceDir.getDirectoryPath(), "Tex");
        ResourceManager::setTextureDirectoryPath(expected);
        Assert::AreEqual(expected, ResourceManager::getTextureDirectoryPath());
      }

      // Set it back to cleanup the test
      ResourceManager::setTextureDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetShaderDirectoryPath)
    {
      Path original = ResourceManager::getShaderDirectoryPath();

      // Do the test
      {
        Path expected(ResourceManager::getResourceDirectoryPath().asString(), "Sha");
        ResourceManager::setShaderDirectoryPath(expected);
        Assert::AreEqual(expected, ResourceManager::getShaderDirectoryPath());

        // Check the shader sub directories are correct
        {
          Path expectedVert(expected.asString(), VERTEX_SHADER_DIR);
          Assert::AreEqual(expectedVert, ResourceManager::getVertexShaderDirectoryPath());
        }

        {
          Path expectedFrag(expected.asString(), FRAGMENT_SHADER_DIR);
          Assert::AreEqual(expectedFrag, ResourceManager::getFragmentShaderDirectoryPath());
        }

        {
          Path expectedGeom(expected.asString(), GEOMETRY_SHADER_DIR);
          Assert::AreEqual(expectedGeom, ResourceManager::getGeometryShaderDirectoryPath());
        }
      }

      // Set it back to cleanup the test
      ResourceManager::setShaderDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetVertexShaderDirectoryPath)
    {
      Path original = ResourceManager::getVertexShaderDirectoryPath();

      // Do the test
      {
        Path expected(ResourceManager::getShaderDirectoryPath().asString(), "Vert");
        ResourceManager::setVertexShaderDirectoryPath(expected);
        Assert::AreEqual(expected, ResourceManager::getVertexShaderDirectoryPath());
      }

      // Set it back to cleanup the test
      ResourceManager::setVertexShaderDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetFragmentShaderDirectoryPath)
    {
      Path original = ResourceManager::getFragmentShaderDirectoryPath();

      // Do the test
      {
        Path expected(ResourceManager::getShaderDirectoryPath().asString(), "Frag");
        ResourceManager::setFragmentShaderDirectoryPath(expected);
        Assert::AreEqual(expected, ResourceManager::getFragmentShaderDirectoryPath());
      }

      // Set it back to cleanup the test
      ResourceManager::setFragmentShaderDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetGeometryShaderDirectoryPath)
    {
      Path original = ResourceManager::getGeometryShaderDirectoryPath();

      // Do the test
      {
        Path expected(ResourceManager::getShaderDirectoryPath().asString(), "Geo");
        ResourceManager::setGeometryShaderDirectoryPath(expected);
        Assert::AreEqual(expected, ResourceManager::getGeometryShaderDirectoryPath());
      }

      // Set it back to cleanup the test
      ResourceManager::setGeometryShaderDirectoryPath(original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_Unloading)
    {
      // Test all the unloading in one method, as we cannot do it over multiple tests since unload is called afterwards

      {
        // Load a texture
        ResourceManager::loadTexture("block.png", GL_TRUE, textureStringId);

        // Check it exists
        Assert::IsNotNull(ResourceManager::getTexture(textureStringId));

        // Unload textures
        ResourceManager::unloadTextures();

        // Check the texture doesn't exist any more (turn off asserts)
        AssertDisabler assertDisabler;
        Assert::IsNull(ResourceManager::getTexture(textureStringId));
      }

      {
        // Disable asserts because geom shader code might not be legit (as it's just a test resource)
        AssertDisabler assertDisabler;

        // Load a shader
        ResourceManager::loadShader("sprite.vs", "sprite.frag", "sprite.geom", shaderStringId);

        // Check it exists
        Assert::IsNotNull(ResourceManager::getShader(shaderStringId));

        // Unload shaders
        ResourceManager::unloadShaders();

        // Check the shader doesn't exist any more
        Assert::IsNull(ResourceManager::getShader(shaderStringId));
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_CollectAllAssetsOnInit)
    {
      ResourceManager::init();

      // Check the textures in the texture directory are found
      {
        Directory textureDirectory(ResourceManager::getTextureDirectoryPath());

        std::vector<File> actualTextures;
        textureDirectory.findFiles(actualTextures);

        for (const File& fileName : actualTextures)
        {
          Assert::IsNotNull(ResourceManager::getTexture(internString(fileName.getFileName())));
        }
      }

      // Check the shaders have been loaded
      {
        Directory shaderDirectory(ResourceManager::getShaderDirectoryPath());

        std::vector<File> actualShaders;
        shaderDirectory.findFiles(actualShaders);

        for (const File& fileName : actualShaders)
        {
          Assert::IsNotNull(ResourceManager::getShader(internString(fileName.getExtensionlessFileName())));
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadShader)
    {
      // Disable asserts for this because geometry shader might be rubbish and not compile
      {
        AssertDisabler disabler;

        Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "sprite.geom", shaderStringId);
        Assert::IsNotNull(shader);
      }

      Shader* shader = ResourceManager::loadShader("colour.vs", "colour.frag", "", shaderStringId);
      Assert::IsNotNull(shader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetShader)
    {
      Shader* expectedShader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "sprite.geom", shaderStringId);
      Shader* actualShader = ResourceManager::getShader(shaderStringId);

      Assert::AreEqual(expectedShader, actualShader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadTexture)
    {
      Texture2D* texture = ResourceManager::loadTexture("block.png", GL_TRUE, textureStringId);
      Assert::IsNotNull(texture);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetTexture)
    {
      Texture2D* expectedTexture = ResourceManager::loadTexture("block.png", GL_TRUE, textureStringId);
      Texture2D* actualTexture = ResourceManager::getTexture(textureStringId);

      Assert::AreEqual(expectedTexture, actualTexture);
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

      template<>
      static std::wstring ToString<Texture2D>(Texture2D* texture)
      {
        return StringUtils::intToWchar((int)texture, 16);
      }

      template<>
      static std::wstring ToString<Path>(const Path& path)
      {
        const std::string& directoryPath = path.asString();
        wchar_t buffer[1024];
        StringUtils::charToWchar(directoryPath.c_str(), buffer, 1024);

        return std::wstring(buffer);
      }
    }
  }
}