#include "stdafx.h"

#include "Factories/GameScreenFactory.h"
#include "Levels/SpaceLevel.h"
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
    transitionToScreen(screen);

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = GameObject::allocate();

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<GameObject>& image = GameObject::allocate(getWindow()->getCamera()->getTransform());
    UI::Image::create(image, "Logo.png", UI::Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent<LoadResourcesAsyncScript>();
    loadResourcesScript->addOnLoadCompleteCallback(&transitionToMainMenuScreen);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToMainMenuScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();
    transitionToScreen(screen);

    const Handle<GameObject>& playGameButton = GameObject::allocate();
    UI::Button::create(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1));

    const Handle<GameObject>& exitGameButton = GameObject::allocate();
    UI::Button::create(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));

    const Handle<GameObject>& buttonStackPanel = GameObject::allocate(getWindow()->getCamera()->getTransform());
    UI::StackPanel::create(buttonStackPanel, UI::StackPanel::VerticalAlignment::kCentre, playGameButton, exitGameButton);
    buttonStackPanel->getTransform()->setTranslation(glm::vec3(getViewportDimensions() * 0.5f, 0));
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreenCallback(const Handle<GameObject>& sender)
  {
    transitionToGameplayScreen(Screen::allocate(), "");
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath)
  {
    transitionToScreen(screen);

    const Handle<GameObject>& ship = GameObject::allocate();
    Ship::create(ship);

    const Handle<GameObject>& shield = GameObject::allocate(ship->getTransform());
    Shield::create(shield);
  }
}