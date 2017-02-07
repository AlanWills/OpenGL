#pragma once

#include "FileSystem/Path.h"
#include "Screens/Screen.h"

using namespace CelesteEngine;


namespace OpenGL
{

class SpaceLevel
{
  public:
    static void load(const Handle<Screen>& screen, const Path& relativeDataFilePath);

  private:
    /// \brief The xml element tag name which holds the relative path to the sprite we will use as a background
    static std::string m_backgroundNodeName;

    /// \brief The xml element tag names which hold the asteroid densities for the asteroid spawner script
    static std::string m_tinyAsteroidNodeName;
    static std::string m_smallAsteroidNodeName;
    static std::string m_largeAsteroidNodeName;
    static std::string m_hugeAsteroidNodeName;

    /// \brief The xml element tag name which holds the spawn point positions
    static std::string m_spawnPoints;
};

}