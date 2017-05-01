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
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Screen>& screen = Screen::allocate();
    transitionToScreen(screen);

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return;
    }

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject();

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<GameObject>& image = screen->allocateGameObject(getWindow()->getCamera()->getTransform());
    Image::create(image, "Logo.png", Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent(LoadResourcesAsyncScript::allocate());
    loadResourcesScript->addOnLoadCompleteCallback(&transitionToMainMenuScreen);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToMainMenuScreen()
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Screen>& screen = Screen::allocate();
    transitionToScreen(screen);

    const Handle<GameObject>& playGameButton = screen->allocateGameObject();
    Button::create(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1));

    const Handle<GameObject>& exitGameButton = screen->allocateGameObject();
    Button::create(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));

    const Handle<GameObject>& buttonStackPanel = screen->allocateGameObject(getWindow()->getCamera()->getTransform());
    StackPanel::create(buttonStackPanel, {playGameButton, exitGameButton}, StackPanel::kVertical);
    buttonStackPanel->getTransform()->setTranslation(glm::vec3(getViewportDimensions() * 0.5f, 0));
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreenCallback(const Handle<GameObject>& sender)
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    transitionToGameplayScreen(Screen::allocate(), "");
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath)
  {
    transitionToScreen(screen);

    const Handle<GameObject>& ship = screen->allocateGameObject();
    Ship::create(ship);

    const Handle<GameObject>& shield = screen->allocateGameObject(ship->getTransform());
    Shield::create(shield);
  }
}