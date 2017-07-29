#include "stdafx.h"

#include "Factories/GameScreenFactory.h"
#include "Objects/GameObject.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/Game.h"
#include "Input/KeyboardVisibilityScript.h"
#include "Physics/RigidBody2D.h"
#include "Animation/StateMachine.h"
#include "Ship/Ship.h"
#include "Ship/Shield.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToSplashScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject();

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<GameObject>& image = screen->allocateGameObject(getWindow()->getCamera()->getTransform());
    UI::Image::create(image, "Logo.png", UI::Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent<LoadResourcesAsyncScript>();
    loadResourcesScript->setWaitTime(3);
    loadResourcesScript->addOnLoadCompleteCallback(&transitionToMainMenuScreen);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToMainMenuScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    const Handle<GameObject>& playGameButton = screen->allocateGameObject();
    UI::Button::create(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1));

    const Handle<GameObject>& exitGameButton = screen->allocateGameObject();
    UI::Button::create(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));
    exitGameButton->addComponent<RigidBody2D>()->setAngularVelocity(0.1f);
    exitGameButton->getTransform()->scale(0.25f, 0.5f, 1);

    const Handle<GameObject>& buttonStackPanel = screen->allocateGameObject(getWindow()->getCamera()->getTransform());
    UI::StackPanel::create(buttonStackPanel, UI::StackPanel::VerticalAlignment::kCentre, playGameButton, exitGameButton);
    buttonStackPanel->getTransform()->setTranslation(getViewportDimensions() * 0.5f);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreenCallback(const Handle<GameObject>& sender)
  {
    //killOwnerScreen(sender);
    transitionToGameplayScreen(Screen::allocate());
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreen(const Handle<Screen>& screen)
  {
    const Handle<GameObject>& ship = screen->allocateGameObject();
    Ship::create(ship);

    //const Handle<GameObject>& shield = screen->createGameObject(ship->getTransform());
    //Shield::create(shield);
  }
}