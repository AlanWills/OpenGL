#pragma once

#include "Screens/Screen.h"

using namespace CelesteEngine;


namespace Space
{
  //------------------------------------------------------------------------------------------------
  DllExport void transitionToGameplayScreen(
    const Handle<Screen>& screen, 
    const std::string& relativeLevelDataFilePath);

  DllExport void transitionToGameplayScreen(
    const Handle<Screen>& screen,
    const Path& relativeLevelDataFilePath);
}