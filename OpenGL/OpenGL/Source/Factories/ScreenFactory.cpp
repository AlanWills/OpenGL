#include "stdafx.h"

#include "Factories/ScreenFactory.h"
#include "Game/GameManager.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Audio/AudioSource.h"
#include "Animation/StateMachine.h"
#include "Scripts/AsteroidSpawningScript.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::allocateScreenAndTransition() const
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return Handle<Screen>();
    }

    Handle<Screen> screen = Screen::allocateAndInitialize();
    GameManager::getScreenManager()->transitionToScreen(screen);

    return screen;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::transitionToSplashScreen() const
  {
    Handle<Screen> screen = allocateScreenAndTransition();

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return Handle<Screen>();
    }

    // Attach the async resource loader to a game object
    Handle<GameObject> resourceLoader = screen->allocateAndInitializeGameObject();
    
    // Add a background image
    addScreenBackground(screen, "Logo.png");

    // Add resource loading whilst we display the splash screen
    resourceLoader->addComponent<kUnmanaged>(LoadResourcesAsyncScript::allocateAndInitialize());

    return screen;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::transitionToMainMenuScreen() const
  {
    Handle<Screen> screen = allocateScreenAndTransition();

    if (!screen->getUIManager().canAllocateButton())
    {
      ASSERT_FAIL();
      return screen;
    }

    Handle<StackPanel> buttonStackPanel = screen->getUIManager().allocateAndInitializeStackPanel();
    buttonStackPanel->setOrientation(StackPanel::kVertical);
    buttonStackPanel->getTransform()->setLocalTranslation(glm::vec3(GameManager::getScreenManager()->getViewportDimensions() * 0.5f, 0));

    Handle<Button> playGameButton = screen->getUIManager().allocateAndInitializeButton();
    playGameButton->addOnLeftClickEvent(std::bind(&ScreenFactory::transitionCallback, *this, std::placeholders::_1));
    playGameButton->setText("Play");

    Handle<Button> exitGameButton = screen->getUIManager().allocateAndInitializeButton();
    exitGameButton->addOnLeftClickEvent(std::bind(&ScreenManager::exitCallback, GameManager::getScreenManager(), std::placeholders::_1));
    exitGameButton->setText("Exit");

    buttonStackPanel->addChild(playGameButton);
    buttonStackPanel->addChild(exitGameButton);

    return screen;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::transitionToGameplayScreen() const
  {
    Handle<Screen> screen = allocateScreenAndTransition();
    //addScreenBackground(screen, Path("Backgrounds", "RainbowNebula.png").as_string());

    Handle<GameObject> asteroidSpawner = screen->allocateAndInitializeGameObject();
    {
      Handle<RectangleCollider> asteroidCollider = asteroidSpawner->addComponent<kManaged>(RectangleCollider::allocateAndInitialize());
      asteroidCollider->setDimensions(GameManager::getScreenManager()->getViewportDimensions());

      Handle<AsteroidSpawningScript> asteroidSpawning = asteroidSpawner->addComponent<kUnmanaged>(AsteroidSpawningScript::allocateAndInitialize());
      /*asteroidSpawning->setTinyAsteroidCount(30);
      asteroidSpawning->setSmallAsteroidCount(20);
      asteroidSpawning->setLargeAsteroidCount(10);*/
      asteroidSpawning->setHugeAsteroidCount(3);
    }

    Handle<GameObject> turret = screen->allocateAndInitializeGameObject();
    {
      Handle<SpriteRenderer> renderer = turret->addComponent<kManaged>(SpriteRenderer::allocateAndInitialize());
      Handle<StateMachine> stateMachine = turret->addComponent<kUnmanaged>(StateMachine::allocateAndInitialize());

      Handle<Animation> idleAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
      idleAnimation->addFrame("ChainBlasterFrame0.png");
      idleAnimation->setSecondsPerFrame(0.1f);
      idleAnimation->setLoop(false);

      Handle<Animation> firingAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
      idleAnimation->addFrame("ChainBlasterFrame0.png");
      firingAnimation->addFrame("ChainBlasterFrame1.png");
      firingAnimation->addFrame("ChainBlasterFrame2.png");

      Handle<AnimationState> idleState = stateMachine->addState(idleAnimation);
      Handle<AnimationState> firingState = stateMachine->addState(firingAnimation);
      stateMachine->setStartingState(idleState);
      idleState->addTransition(firingState, std::bind(&ScreenFactory::firing, *this));
      firingState->addTransition(idleState, std::bind(&ScreenFactory::notFiring, *this));
    }

    return screen;
  }

  //------------------------------------------------------------------------------------------------
  void ScreenFactory::addScreenBackground(const Handle<Screen>& screen, const std::string& relativeImagePath) const
  {
    const glm::vec2& screenDimensions = GameManager::getScreenManager()->getViewportDimensions();

    Handle<Image> image = screen->getUIManager().allocateAndInitializeImage();
    image->setImage(relativeImagePath);
    image->setSize(screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, -0.1f));
  }

  //------------------------------------------------------------------------------------------------
  void ScreenFactory::transitionCallback(Handle<GameObject> sender)
  {
    transitionToGameplayScreen();
  }

  //------------------------------------------------------------------------------------------------
  bool ScreenFactory::firing()
  {
    return GameManager::getInputManager()->getKeyboard()->isKeyDown(GLFW_KEY_SPACE);
  }
}