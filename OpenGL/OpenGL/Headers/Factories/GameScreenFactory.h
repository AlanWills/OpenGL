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
    static void transitionToGameplayScreenCallback(const Handle<GameObject>& gameObject);

    static void createTerminalScreen(const Handle<Screen>& screen);

  private:
    static void createGameplayScreen(const Handle<Screen>& screen);
    static void runCodeAndActivateGameplayScreen(const Handle<GameObject>& gameObject);
};
}