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
    static void createGameplayScreen(const Handle<Screen>& screen);
};
}