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

    static void createGameplayScreen(const Handle<Screen>& screen);
    static void createTerminalScreen(const Handle<Screen>& screen);

  private:
    static void runCode(const Handle<GameObject>& gameObject);
};
}