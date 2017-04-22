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


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void transitionToSplashScreen()
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Screen>& screen = Screen::allocate();

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return;
    }

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject();

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    Handle<Image> image = screen->getUIManager().allocateImage();
    createImage(image, "Logo.png", Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = LoadResourcesAsyncScript::allocate();
    loadResourcesScript->addOnLoadCompleteCallback(&transitionToMainMenuScreen);
    resourceLoader->addComponent<kUnmanaged>(loadResourcesScript);

    transitionToScreen(screen);
  }

  //------------------------------------------------------------------------------------------------
  void transitionToMainMenuScreen()
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Screen>& screen = Screen::allocate();

    if (!screen->getUIManager().canAllocateButton(2))
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Button>& playGameButton = screen->getUIManager().allocateButton();
    createButton(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1), "AsteroidLevel.xml");

    const Handle<Button>& exitGameButton = screen->getUIManager().allocateButton();
    createButton(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));

    const Handle<StackPanel>& buttonStackPanel = screen->getUIManager().allocateStackPanel();
    buttonStackPanel->setOrientation(StackPanel::kVertical);
    buttonStackPanel->getTransform()->setTranslation(glm::vec3(getViewportDimensions() * 0.5f, 0));
    buttonStackPanel->addChild(playGameButton);
    buttonStackPanel->addChild(exitGameButton);

    transitionToScreen(screen);
  }

  //------------------------------------------------------------------------------------------------
  void transitionToGameplayScreenCallback(const Handle<Component>& sender)
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }
    const Handle<Screen>& screen = Screen::allocate();

    ASSERT(sender.is<Button>());
    transitionToGameplayScreen(screen, sender.as<Button>()->getUserData());
  }

  //------------------------------------------------------------------------------------------------
  void transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath)
  {
    transitionToScreen(screen);

    const Handle<CelesteEngine::GameObject>& ship = screen->allocateGameObject();
    Ship::createShip(ship);
  }
}