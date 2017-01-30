#pragma once

#include "FileSystem/File.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace Kernel;


namespace OpenGL
{

class Data
{
  public:
    Data();

    // XMLDocument does not support copying, so neither can this
    Data(const Data& data) = delete;

    void generate(const Path& fullFilePath);

    const XMLElement* getNode(const std::string& nodeName) const;
    const char* getNodeDataAsText(const std::string& nodeName) const;
    float getNodeDataAsFloat(const std::string& nodeName) const;

  private:
    tinyxml2::XMLDocument m_document;
};

}