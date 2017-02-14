#pragma once

#include "Screens/Screen.h"

using namespace CelesteEngine;


namespace Game
{
  //------------------------------------------------------------------------------------------------
  void transitionToSplashScreen();
  void transitionToMainMenuScreen();

  void transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath);
  void transitionToGameplayScreen(const Handle<Screen>& screen, const Path& relativeLevelDataFilePath);
  void transitionToGameplayScreenCallback(const Handle<Component>& screen);
}