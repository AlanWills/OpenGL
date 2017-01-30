#include "stdafx.h"

#include "Resources/Data.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Data::Data() :
    m_document()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Data::generate(const Path& fullFilePath)
  {
    XMLError result = m_document.LoadFile(fullFilePath.as_string().c_str());
    ASSERT(result == XML_SUCCESS);
  }

  //------------------------------------------------------------------------------------------------
  const XMLElement* Data::getNode(const std::string& nodeName) const
  {
    const XMLElement* node = m_document.RootElement()->FirstChildElement(nodeName.c_str());
    ASSERT(node);

    return node;
  }

  //------------------------------------------------------------------------------------------------
  const char* Data::getNodeDataAsText(const std::string& nodeName) const
  {
    const XMLElement* node = getNode(nodeName);
    ASSERT(node);

    const char* value = node->GetText();
    ASSERT(value);
    
    return value;
  }

  //------------------------------------------------------------------------------------------------
  float Data::getNodeDataAsFloat(const std::string& nodeName) const
  {
    const XMLElement* node = getNode(nodeName);
    ASSERT(node);

    float value = 0;
    XMLError result = node->QueryFloatText(&value);
    ASSERT(result == XML_SUCCESS);

    return value;
  }
}