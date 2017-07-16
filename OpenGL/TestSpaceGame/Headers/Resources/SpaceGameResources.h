#pragma once

#include "Resources/Resources.h"


namespace TestSpaceGame
{
  
class SpaceGameResources : public TestUtils::Resources
{
  public:
    SpaceGameResources() { }
    ~SpaceGameResources() { }

    SpaceGameResources(const SpaceGameResources&) = delete;
    SpaceGameResources& operator=(const SpaceGameResources&) = delete;

  public:
    TEST_DATA(InvalidShipData, "InvalidShipData.xml")
    TEST_DATA(ValidShipData, "ValidShipData.xml")
};

}