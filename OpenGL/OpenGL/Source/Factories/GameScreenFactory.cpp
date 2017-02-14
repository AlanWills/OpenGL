#include "stdafx.h"

#include "Factories/GameScreenFactory.h"
#include "Levels/SpaceLevel.h"
#include "Objects/GameObject.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/GameManager.h"
#include "Input/KeyboardVisibilityScript.h"


namespace Game
{
  //------------------------------------------------------------------------------------------------
  void transitionToSplashScreen()
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Screen>& screen = Screen::allocateAndInitialize();

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return;
    }

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateAndInitializeGameObject();

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    Handle<Image> image = screen->getUIManager().allocateAndInitializeImage();
    createImage(image, "Logo.png", screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = LoadResourcesAsyncScript::allocateAndInitialize();
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

    const Handle<Screen>& screen = Screen::allocateAndInitialize();

    if (!screen->getUIManager().canAllocateButton(2))
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<Button>& playGameButton = screen->getUIManager().allocateAndInitializeButton();
    createButton(playGameButton, "Play", std::bind(&transitionToGameplayScreenCallback, std::placeholders::_1), "AsteroidLevel.xml");

    const Handle<Button>& exitGameButton = screen->getUIManager().allocateAndInitializeButton();
    createButton(exitGameButton, "Exit", std::bind(&GameManager::exitCallback, std::placeholders::_1));

    const Handle<StackPanel>& buttonStackPanel = screen->getUIManager().allocateAndInitializeStackPanel();
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
    const Handle<Screen>& screen = Screen::allocateAndInitialize();

    ASSERT(sender.is<Button>());
    transitionToGameplayScreen(screen, sender.as<Button>()->getUserData());
  }

  //------------------------------------------------------------------------------------------------
  void transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath)
  {
    // Take the data file and process the contents
    SpaceLevel::load(screen, relativeLevelDataFilePath);

    const glm::vec2& screenDimensions = getViewportDimensions();

    // Find all the spawn points and create the map UI
    if (screen->getUIManager().canAllocateImage())
    {
      const Handle<Image>& map = screen->getUIManager().allocateAndInitializeImage();
      createImage(map, Path("Sprites", "UI", "Rectangle.png"), screenDimensions * 0.5f);
      addKeyboardVisibilityScript(map, GLFW_KEY_TAB, KeyboardVisibilityScript::kContinuous);

      map->getTransform()->setTranslation(glm::vec3(screenDimensions.x * 0.5f, screenDimensions.y * 0.5f, 0));
      map->setColour(0, 0, 0.5f, 0.5f);
      map->setShouldRender(false);
    }

    /*Handle<GameObject> turret = screen->allocateAndInitializeGameObject();
    {
      const Handle<RigidBody2D>& rigidBody2D = turret->addComponent<kManaged>(RigidBody2D::allocateAndInitialize());
      rigidBody2D->setAngularVelocity(0.1f);

      const Handle<SpriteRenderer>& renderer = turret->addComponent<kManaged>(SpriteRenderer::allocateAndInitialize());
      const Handle<StateMachine>& stateMachine = turret->addComponent<kUnmanaged>(StateMachine::allocateAndInitialize());

      const Handle<Animation>& idleAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
      idleAnimation->addFrame("ChainBlasterFrame0.png");
      idleAnimation->setSecondsPerFrame(0.1f);
      idleAnimation->setLoop(false);

      const Handle<Animation>& firingAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
      idleAnimation->addFrame("ChainBlasterFrame0.png");
      firingAnimation->addFrame("ChainBlasterFrame1.png");
      firingAnimation->addFrame("ChainBlasterFrame2.png");

      const Handle<AnimationState>& idleState = stateMachine->addState(idleAnimation);
      const Handle<AnimationState>& firingState = stateMachine->addState(firingAnimation);
      stateMachine->setStartingState(idleState);
      idleState->addTransition(firingState, std::bind(&ScreenFactory::firing, *this));
      firingState->addTransition(idleState, std::bind(&ScreenFactory::notFiring, *this));
    }*/

    transitionToScreen(screen);
  }

  //------------------------------------------------------------------------------------------------
  void transitionToGameplayScreen(const Handle<Screen>& screen, const Path& relativeLevelDataFilePath)
  {
    transitionToGameplayScreen(screen, relativeLevelDataFilePath.as_string());
  }
}