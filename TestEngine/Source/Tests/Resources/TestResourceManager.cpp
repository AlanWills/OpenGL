#include "stdafx.h"

#include "Resources/ResourceManager.h"

using namespace Engine;


namespace TestEngine
{
  static Path resourceDirPath(Directory::getExecutingAppDirectory(), "..\\..\\TestEngine\\TestResources");
  static StringId shaderStringId = internString("sprite");
  static StringId textureStringId = internString("texture");

  TEST_CLASS(TestResourceManager), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetResourceDirectoryPath)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Path expected(Directory::getExecutingAppDirectory(), "Res");
      resourceManager.setResourceDirectoryPath(expected);

      Assert::AreEqual(expected, resourceManager.getResourceDirectoryPath());

      // Check shader and texture dirs have been updated
      {
        Path expectedText(expected.asString(), TEXTURE_DIR);
        Assert::AreEqual(expectedText, resourceManager.getTextureDirectoryPath());
      }

      {
        Path expectedShad(expected.asString(), SHADER_DIR);
        Assert::AreEqual(expectedShad, resourceManager.getShaderDirectoryPath());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetTextureDirectoryPath)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Path expected(resourceDirPath.asString(), "Tex");
      resourceManager.setTextureDirectoryPath(expected);
      Assert::AreEqual(expected, resourceManager.getTextureDirectoryPath());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetShaderDirectoryPath)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Path expected(resourceManager.getResourceDirectoryPath().asString(), "Sha");
      resourceManager.setShaderDirectoryPath(expected);
      Assert::AreEqual(expected, resourceManager.getShaderDirectoryPath());

      // Check the shader sub directories are correct
      {
        Path expectedVert(expected.asString(), VERTEX_SHADER_DIR);
        Assert::AreEqual(expectedVert, resourceManager.getVertexShaderDirectoryPath());
      }

      {
        Path expectedFrag(expected.asString(), FRAGMENT_SHADER_DIR);
        Assert::AreEqual(expectedFrag, resourceManager.getFragmentShaderDirectoryPath());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetVertexShaderDirectoryPath)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Path expected(resourceManager.getShaderDirectoryPath().asString(), "Vert");
      resourceManager.setVertexShaderDirectoryPath(expected);
      Assert::AreEqual(expected, resourceManager.getVertexShaderDirectoryPath());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_SetFragmentShaderDirectoryPath)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Path expected(resourceManager.getShaderDirectoryPath().asString(), "Frag");
      resourceManager.setFragmentShaderDirectoryPath(expected);
      Assert::AreEqual(expected, resourceManager.getFragmentShaderDirectoryPath());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_UnloadTextures)
    {
      ResourceManager resourceManager(resourceDirPath.asString());
      AssertDisabler assertDisabler;

      // Load a texture
      resourceManager.loadTexture("block.png", GL_TRUE, textureStringId);

      // Check it exists
      Assert::IsNotNull(resourceManager.getTexture(textureStringId));

      // Unload textures
      resourceManager.unloadTextures();

      // Check the texture doesn't exist any more
      Assert::IsNull(resourceManager.getTexture(textureStringId));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_UnloadShaders)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      // Disable asserts because geom shader code might not be legit (as it's just a test resource)
      AssertDisabler assertDisabler;

      // Load a shader
      resourceManager.loadShader("sprite.vs", "sprite.frag", shaderStringId);

      // Check it exists
      Assert::IsNotNull(resourceManager.getShader(shaderStringId));

      // Unload shaders
      resourceManager.unloadShaders();

      // Check the shader doesn't exist any more
      Assert::IsNull(resourceManager.getShader(shaderStringId));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_UnloadAllAssets)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      AssertDisabler assertDisabler;

      // Load a texture
      resourceManager.loadTexture("block.png", GL_TRUE, textureStringId);

      // Check it exists
      Assert::IsNotNull(resourceManager.getTexture(textureStringId));

      // Load a shader
      resourceManager.loadShader("sprite.vs", "sprite.frag", shaderStringId);

      // Check it exists
      Assert::IsNotNull(resourceManager.getShader(shaderStringId));

      // Unload everything
      resourceManager.unloadAllAssets();

      // Check the texture doesn't exist any more
      Assert::IsNull(resourceManager.getTexture(textureStringId));

      // Check the shader doesn't exist any more
      Assert::IsNull(resourceManager.getShader(shaderStringId));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_CollectAllAssetsOnInit)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      resourceManager.init();

      // Check the textures in the texture directory are found
      {
        Directory textureDirectory(resourceManager.getTextureDirectoryPath());

        std::vector<File> actualTextures;
        textureDirectory.findFiles(actualTextures);

        for (const File& fileName : actualTextures)
        {
          Assert::IsNotNull(resourceManager.getTexture(internString(fileName.getFileName())));
        }
      }

      // Check the shaders have been loaded
      {
        Directory shaderDirectory(resourceManager.getShaderDirectoryPath());

        std::vector<File> actualShaders;
        shaderDirectory.findFiles(actualShaders);

        for (const File& fileName : actualShaders)
        {
          Assert::IsNotNull(resourceManager.getShader(internString(fileName.getExtensionlessFileName())));
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadShader)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Shader* shader = resourceManager.loadShader("sprite.vs", "sprite.frag", shaderStringId);
      Assert::IsNotNull(shader);

      shader = resourceManager.loadShader("colour.vs", "colour.frag", shaderStringId);
      Assert::IsNotNull(shader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetShader)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Shader* expectedShader = resourceManager.loadShader("sprite.vs", "sprite.frag", shaderStringId);
      Shader* actualShader = resourceManager.getShader(shaderStringId);

      Assert::AreEqual(expectedShader, actualShader);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_LoadTexture)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Texture2D* texture = resourceManager.loadTexture("block.png", GL_TRUE, textureStringId);
      Assert::IsNotNull(texture);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_ResourceManager_GetTexture)
    {
      ResourceManager resourceManager(resourceDirPath.asString());

      Texture2D* expectedTexture = resourceManager.loadTexture("block.png", GL_TRUE, textureStringId);
      Texture2D* actualTexture = resourceManager.getTexture(textureStringId);

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