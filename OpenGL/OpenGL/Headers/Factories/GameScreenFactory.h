#pragma once

#include "Screens/Screen.h"

using namespace CelesteEngine;


namespace SpaceGame
{

class GameScreenFactory
{
  public:
    //------------------------------------------------------------------------------------------------
    static void transitionToSplashScreen();
    static void transitionToMainMenuScreen();
    
    static void transitionToGameplayScreenCallback(const Handle<GameObject>& screen);
    static void transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath);
    static void transitionToGameplayScreen(const Handle<Screen>& screen, const Path& relativeLevelDataFilePath) 
    { 
      transitionToGameplayScreen(screen, relativeLevelDataFilePath.as_string()); 
    }
};
}