#include "stdafx.h"

#include "Factories/GameScreenFactory.h"
#include "Objects/GameObject.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/Game.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Physics/RigidBody2D.h"
#include "Animation/StateMachine.h""
#include "UI/TextBox.h"
#include "UI/ToolTip.h"
#include "UI/ComputerInteractionUI.h"


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
    UI::Image::create(image, Path("Sprites", "UI", "Logo.png"), UI::Image::kPreserveAspectRatio, screenDimensions);
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
    sender->getOwnerScreen()->die();
    createGameplayScreen(Screen::allocate());
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::createGameplayScreen(const Handle<Screen>& screen)
  {
    screen->setName("Gameplay");
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& floor = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& floorRenderer = SpriteRenderer::create(floor, Path("Sprites", "UI", "Rectangle.png"));
    floorRenderer->setColour(glm::vec4(1, 1, 1, 1));
    floor->setName("Floor");

    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    floor->getTransform()->setScale(floorSize / floorRenderer->getDimensions());
    floor->getTransform()->setTranslation(floorSize * 0.5f);

    const Handle<GameObject>& door = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& doorRenderer = SpriteRenderer::create(door, Path("Sprites", "MetalDoor.png"));
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
    player->getTransform()->setTranslation(viewportDimensions.x * 0.25f, floorSize.y + playerSize.y * 0.5f);

    const Handle<RectangleCollider>& playerCollider = player->addComponent<RectangleCollider>();
    playerCollider->setDimensions(playerRenderer->getDimensions());

    const Handle<KeyboardRigidBody2DController>& playerMovement = player->addComponent<KeyboardRigidBody2DController>();
    playerMovement->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    playerMovement->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    playerMovement->setLinearVelocityDelta(10, 0);
    playerMovement->setIncrementMode(KeyboardRigidBody2DController::kToggle);

    const Handle<GameObject>& terminal = screen->allocateGameObject(Layer::kGUI);
    const Handle<SpriteRenderer>& terminalRenderer = SpriteRenderer::create(terminal, Path("Sprites", "ComputerTerminal.png"));

    glm::vec2 terminalSize = glm::vec2(90, 90);
    terminal->getTransform()->setScale(terminalSize / terminalRenderer->getDimensions());
    terminal->getTransform()->setTranslation(viewportDimensions.x * 0.5f, floorSize.y + terminalSize.y * 0.5f);
    
    const Handle<RectangleCollider>& terminalCollider = terminal->addComponent<RectangleCollider>();
    terminalCollider->setDimensions(terminalRenderer->getDimensions());
    
    terminal->addComponent<SpaceGameUI::ComputerInteractionUI>();
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::createTerminalScreen(const Handle<Screen>& screen)
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    {
      const Handle<GameObject>& terminalTextBox = screen->allocateGameObject(kGUI);
      terminalTextBox->getTransform()->setTranslation(viewportDimensions.x * 0.25f, viewportDimensions.y);

      const Handle<TextRenderer>& terminalRenderer = createTextRenderer(
        terminalTextBox,
        "bool isDoorOpen = false;",
        24,
        viewportDimensions.x * 0.5f,
        Horizontal::kLeft,
        Vertical::kTop);
      const Handle<TextBox>& textBox = terminalTextBox->addComponent<TextBox>();

      const Handle<GameObject>& boolToolTip = screen->allocateGameObject(kGUI, terminalTextBox->getTransform());
      const glm::vec2& boolSize = terminalRenderer->getFont().measureString("bool");
      boolToolTip->getTransform()->setTranslation(boolSize.x * 0.5f - viewportDimensions.x * 0.25f,-boolSize.y * 0.5f - 50, 0.01f);

      const Handle<ToolTip>& toolTip = boolToolTip->addComponent<ToolTip>();
      const Handle<RectangleCollider>& rectangleCollider = boolToolTip->addComponent<RectangleCollider>();
      rectangleCollider->setDimensions(boolSize);
      rectangleCollider->setOffset(glm::vec2(0, 50));

      const Handle<TextRenderer>& toolTipTextRenderer = createTextRenderer(
        boolToolTip,
        "bool",
        12,
        boolSize.x,
        Horizontal::kLeft,
        Vertical::kCentre);
      toolTipTextRenderer->setColour(0, 1.0f, 1.0f, 1);
    }

    {
      const Handle<GameObject>& descriptionLabel = screen->allocateGameObject(kGUI);
      descriptionLabel->getTransform()->setTranslation(viewportDimensions.x * 0.75f, viewportDimensions.y);

      const Handle<TextRenderer>& descriptionRenderer = createTextRenderer(
        descriptionLabel,
        "Ah yes, the  'bool' - the computer equivalent of yes and no.\
        \n\nIt can only have two values: true (yes) or false (no), but is really useful.\
        \n\nThis bool is currently set to false and is called 'isDoorOpen'...", 
        24, 
        viewportDimensions.x * 0.5f,
        Horizontal::kLeft,
        Vertical::kTop);
    }

    {
      const Handle<GameObject>& runCodeButton = screen->allocateGameObject(kGUI);
      const Handle<Button>& button = Button::create(runCodeButton, "Run Code", std::bind(&GameScreenFactory::runCodeAndActivateGameplayScreen, std::placeholders::_1));
      runCodeButton->getTransform()->setTranslation(viewportDimensions.x * 0.5f, button->getSpriteRenderer()->getDimensions().y);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameScreenFactory::runCodeAndActivateGameplayScreen(const Handle<GameObject>& gameObject)
  {
    gameObject->getOwnerScreen()->die();
    activateScreen(getScreenManager()->findScreen("Gameplay"));
  }
}