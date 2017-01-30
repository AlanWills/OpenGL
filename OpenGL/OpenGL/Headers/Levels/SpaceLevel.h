#pragma once

#include "FileSystem/Path.h"
#include "Screens/Screen.h"

using namespace Kernel;


namespace OpenGL
{

class SpaceLevel
{
  public:
    static void load(const Path& relativeDataFilePath, const Handle<Screen>& screen);

  private:
    /// \brief The xml element tag name which holds the relative path to the sprite we will use as a background
    static std::string m_backgroundNodeName;
};

}