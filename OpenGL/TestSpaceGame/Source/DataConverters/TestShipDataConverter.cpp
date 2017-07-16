#include "stdafx.h"

#include "DataConverters/ShipDataConverter.h"


namespace TestSpaceGame
{		
	TEST_CLASS(TestShipDataConverter), CelesteUnitTest
	{
	public:
		
#pragma region Constructor Tests

    /*
      ValidShipData.xml contents

      <Root>
        <TextureRelativePath>Relative\Path.jpg</TextureRelativePath>
        <LinearSpeed>12</LinearSpeed>
        <AngularSpeed>0.123</AngularSpeed>
      </Root>
    */

    /*
      InvalidShipData.xml contents

      <Root>
        <TextureRelativePath>Another\Path.jpg</TextureRelativePath>
        <LinearSpeed>asdvsd</LinearSpeed>
        <AngularSpeed>0.123</AngularSpeed>
      </Root>
    */

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorData_InputtingNullHandle_DoesNothing)
		{
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(ConstHandle<Data>());

      Assert::AreEqual(0.0f, converter.getAngularSpeed());
      Assert::AreEqual(0.0f, converter.getLinearSpeed());
      Assert::AreEqual("", converter.getTextureRelativePath().c_str());
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorData_ContainingInvalidXml_LoadsAsMuchDataAsItCan)
    {
      const Handle<Data>& invalidData = getResourceManager()->loadData(SpaceGameResources::getInvalidShipDataRelativePath());
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(invalidData.as_const());

      Assert::AreEqual(0.123f, converter.getAngularSpeed());
      Assert::AreEqual(0.0f, converter.getLinearSpeed());
      Assert::AreEqual("Another\\Path.jpg", converter.getTextureRelativePath().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorData_ContainingValidXml_LoadsData)
    {
      const Handle<Data>& validData = getResourceManager()->loadData(SpaceGameResources::getValidShipDataRelativePath());
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(validData.as_const());

      Assert::AreEqual(0.123f, converter.getAngularSpeed());
      Assert::AreEqual(12.0f, converter.getLinearSpeed());
      Assert::AreEqual("Relative\\Path.jpg", converter.getTextureRelativePath().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorXmlElement_InputtingNullElement_DoesNothing)
    {
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(nullptr);

      Assert::AreEqual(0.0f, converter.getAngularSpeed());
      Assert::AreEqual(0.0f, converter.getLinearSpeed());
      Assert::AreEqual("", converter.getTextureRelativePath().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorXmlElement_ContainingInvalidXml_LoadsAsMuchDataAsItCan)
    {
      const Handle<Data>& invalidData = getResourceManager()->loadData(SpaceGameResources::getInvalidShipDataRelativePath());
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(invalidData->getDocumentRoot());

      Assert::AreEqual(0.123f, converter.getAngularSpeed());
      Assert::AreEqual(0.0f, converter.getLinearSpeed());
      Assert::AreEqual("Another\\Path.jpg", converter.getTextureRelativePath().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ShipDataConverter_ConstructorXmlElement_ContainingValidXml_LoadsData)
    {
      const Handle<Data>& validData = getResourceManager()->loadData(SpaceGameResources::getValidShipDataRelativePath());
      SpaceGame::ShipDataConverter converter = SpaceGame::ShipDataConverter(validData->getDocumentRoot());

      Assert::AreEqual(0.123f, converter.getAngularSpeed());
      Assert::AreEqual(12.0f, converter.getLinearSpeed());
      Assert::AreEqual("Relative\\Path.jpg", converter.getTextureRelativePath().c_str());
    }

#pragma endregion

	};
}