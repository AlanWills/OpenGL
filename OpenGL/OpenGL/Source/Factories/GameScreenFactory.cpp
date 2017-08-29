#include "stdafx.h"

#include "Factories/GameScreenFactory.h"
#include "Objects/GameObject.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/Game.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Physics/RigidBody2D.h"
#include "Animation/StateMachine.h"
#include "Ship/Ship.h"
#include "Ship/Shield.h"
#include "UI/TextBox.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToSplashScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject(kWorld);

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<GameObject>& image = screen->allocateGameObject(kGUI);
    UI::Image::create(image, "Logo.png", UI::Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->setTranslation(screenDimensions * 0.5f);

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent<LoadResourcesAsyncScript>();
    loadResourcesScript->setWaitTime(1);
    loadResourcesScript->getLoadCompleteEvent().subscribe(&transitionToMainMenuScreen);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToMainMenuScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    const Handle<GameObject>& playGameButton = screen->allocateGameObject(kGUI);
    UI::Button::create(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1));

    const Handle<GameObject>& exitGameButton = screen->allocateGameObject(kGUI);
    UI::Button::create(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));
    
    const Handle<GameObject>& buttonStackPanel = screen->allocateGameObject(kGUI);
    buttonStackPanel->getTransform()->setTranslation(getViewportDimensions() * 0.5f);
    UI::StackPanel::create(buttonStackPanel, UI::StackPanel::VerticalAlignment::kCentre, playGameButton, exitGameButton);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::transitionToGameplayScreenCallback(const Handle<GameObject>& sender)
  {
    killOwnerScreen(sender);
    createTerminalScreen(Screen::allocate());
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::createGameplayScreen(const Handle<Screen>& screen)
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& floor = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& floorRenderer = SpriteRenderer::create(floor, Path("Sprites", "UI", "Rectangle.png"));
    floorRenderer->setColour(glm::vec4(1, 1, 1, 1));
    floor->setName("Floor");

    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    floor->getTransform()->setScale(floorSize / floorRenderer->getDimensions());
    floor->getTransform()->setTranslation(floorSize * 0.5f);

    const Handle<GameObject>& door = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& doorRenderer = SpriteRenderer::create(door, Path("Sprites", "UI", "Rectangle.png"));
    doorRenderer->setColour(glm::vec4(0.5f, 0.5f, 0.5f, 1));
    door->setName("Door");

    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    door->getTransform()->setScale(doorSize / doorRenderer->getDimensions());
    door->getTransform()->setTranslation(viewportDimensions.x - doorSize.x * 0.5f, doorSize.y * 0.5f + floorSize.y);

    const Handle<GameObject>& player = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& playerRenderer = SpriteRenderer::create(player, Path("Sprites", "UI", "Rectangle.png"));
    playerRenderer->setColour(glm::vec4(0, 0, 1, 1));
    player->setName("Player");

    glm::vec2 playerSize = glm::vec2(100, 100);
    player->getTransform()->setScale(playerSize / playerRenderer->getDimensions());
    player->getTransform()->setTranslation(viewportDimensions.x * 0.5f, floorSize.y + playerSize.y * 0.5f);

    const Handle<KeyboardRigidBody2DController>& playerMovement = player->addComponent<KeyboardRigidBody2DController>();
    playerMovement->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    playerMovement->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    playerMovement->setLinearVelocityDelta(10, 0);
    playerMovement->setIncrementMode(KeyboardRigidBody2DController::kToggle);

    const Handle<GameObject>& terminal = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& terminalRenderer = SpriteRenderer::create(terminal, Path("Sprites", "UI", "Rectangle.png"));
    terminalRenderer->setColour(glm::vec4(0.1f, 0.1f, 0.1f, 1));

    glm::vec2 terminalSize = glm::vec2(90, 150);
    terminal->getTransform()->setScale(terminalSize / terminalRenderer->getDimensions());
    terminal->getTransform()->setTranslation(viewportDimensions.x * 0.5f, floorSize.y + terminalSize.y * 0.5f);
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::createTerminalScreen(const Handle<Screen>& screen)
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& terminalTextBox = screen->allocateGameObject(kGUI);
    terminalTextBox->getTransform()->setTranslation(viewportDimensions.x * 0.25f, viewportDimensions.y);

    const Handle<TextRenderer>& terminalRenderer = terminalTextBox->addComponent<TextRenderer>();
    terminalRenderer->setMaxWidth(viewportDimensions.x * 0.5f);
    terminalRenderer->setHorizontalAlignment(Horizontal::kLeft);
    terminalRenderer->setVerticalAlignment(Vertical::kTop);
    terminalRenderer->setFontHeight(24);
    terminalRenderer->setText("bool isDoorOpen = false;");

    const Handle<TextBox>& textBox = terminalTextBox->addComponent<TextBox>();

    const Handle<GameObject>& descriptionLabel = screen->allocateGameObject(kGUI);
    descriptionLabel->getTransform()->setTranslation(viewportDimensions.x * 0.75f, viewportDimensions.y);
    
    const Handle<TextRenderer>& descriptionRenderer = descriptionLabel->addComponent<TextRenderer>();
    descriptionRenderer->setMaxWidth(viewportDimensions.x * 0.5f);
    descriptionRenderer->setHorizontalAlignment(Horizontal::kLeft);
    descriptionRenderer->setVerticalAlignment(Vertical::kTop);
    descriptionRenderer->setFontHeight(24);
    descriptionRenderer->setText(
      "Ah yes, the good ol' 'bool' - computers love dealing in yes and no and that is what a bool is for.\
       \n\nIt can only have two values: true (yes) or false (no), but is really useful.\
       \n\nThis bool is currently set to false and is called 'isDoorOpen'...");
  }
}