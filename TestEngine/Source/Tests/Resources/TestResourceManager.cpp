#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace Engine
{
  // Need these to keep the compiler happy I think
  Path                  ResourceManager::m_resourceDirectoryPath(Directory::getExecutingAppDirectory(), DIRECTORY);
  Path                  ResourceManager::m_textureDirectoryPath(m_resourceDirectoryPath.asString(), TEXTURE_DIR);
  Path                  ResourceManager::m_shaderDirectoryPath(m_resourceDirectoryPath.asString(), SHADER_DIR);
  Path                  ResourceManager::m_vertexShaderDirectoryPath(m_shaderDirectoryPath.asString(), VERTEX_SHADER_DIR);
  Path                  ResourceManager::m_fragmentShaderDirectoryPath(m_shaderDirectoryPath.asString(), FRAGMENT_SHADER_DIR);
  Path                  ResourceManager::m_geometryShaderDirectoryPath(m_shaderDirectoryPath.asString(), GEOMETRY_SHADER_DIR);
}

namespace TestEngine
{
  static Directory testResourceDir(Directory::getExecutingAppDirectory());
  static StringId shaderStringId = internString("sprite");
  static StringId textureStringId = internString("texture");

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
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetTextureDirectoryPath)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetShaderDirectoryPath)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetVertexShaderDirectoryPath)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetFragmentShaderDirectoryPath)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetGeometryShaderDirectoryPath)
    {
      Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_Unloading)
    {
      // Test all the unloading in one method, as we cannot do it over multiple tests since unload is called afterwards

      {
        // Load a texture
        ResourceManager::loadTexture("block", GL_TRUE, textureStringId);

        // Check it exists
        Assert::IsNotNull(ResourceManager::getTexture(textureStringId));

        // Unload textures
        ResourceManager::unloadTextures();

        // Check the texture doesn't exist any more (turn off asserts)
        AssertDisabler assertDisabler;
        Assert::IsNull(ResourceManager::getTexture(textureStringId));
      }

      {
        // Load a shader
        ResourceManager::loadShader("sprite.vs", "sprite.frag", "geom.frag", shaderStringId);

        // Check it exists
        Assert::IsNotNull(ResourceManager::getShader(shaderStringId));

        // Unload shaders
        ResourceManager::unloadShaders();

        // Check the shader doesn't exist any more (turn off asserts)
        AssertDisabler assertDisabler;
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
      Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", "sprite.geom", shaderStringId);
      Assert::IsNotNull(shader);

      shader = ResourceManager::loadShader("colour.vs", "colour.frag", "", shaderStringId);
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
    }
  }
}