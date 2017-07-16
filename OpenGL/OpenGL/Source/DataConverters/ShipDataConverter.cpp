#include "stdafx.h"

#include "DataConverters/ShipDataConverter.h"
#include "Resources/Data.h"


namespace SpaceGame
{
  // Initialise static variables
  std::string ShipDataConverter::m_TextureRelativePathElement = "TextureRelativePath";
  std::string ShipDataConverter::m_LinearSpeedElement = "LinearSpeed";
  std::string ShipDataConverter::m_AngularSpeedElement = "AngularSpeed";

  //------------------------------------------------------------------------------------------------
  ShipDataConverter::ShipDataConverter(const ConstHandle<Data>& dataFile) :
    Inherited(dataFile),
    m_LinearSpeed(0),
    m_AngularSpeed(0),
    m_TextureRelativePath("")
  {
    if (dataFile.is_null())
    {
      ASSERT_FAIL();
      return;
    }

    load(dataFile->getDocumentRoot());
  }

  //------------------------------------------------------------------------------------------------
  ShipDataConverter::ShipDataConverter(const XMLElement* element) :
    Inherited(element),
    m_LinearSpeed(0),
    m_AngularSpeed(0),
    m_TextureRelativePath("")
  {
    load(element);
  }

  //------------------------------------------------------------------------------------------------
  void ShipDataConverter::load(const XMLElement* element)
  {
    if (element == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    if (!getChildElementData(element, m_TextureRelativePathElement, m_TextureRelativePath))
    {
      ASSERT_FAIL();
    }

    if (!getChildElementData(element, m_LinearSpeedElement, m_LinearSpeed))
    {
      ASSERT_FAIL();
    }

    if (!getChildElementData(element, m_AngularSpeedElement, m_AngularSpeed))
    {
      ASSERT_FAIL();
    }
  }
}