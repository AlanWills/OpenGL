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
    createImage(image, "Logo.png", Image::kPreserveAspect, screenDimensions);
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
    createButton(exitGameButton, "Exit", std::bind(&GameManager::exitCallback, std::placeholders::_1));

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
    // Take the data file and process the contents
    SpaceLevel::load(screen, relativeLevelDataFilePath);

    const Handle<CelesteEngine::GameObject>& screenBounds = screen->findGameObjectWithName("LevelBounds");
    if (!screenBounds.get())
    {
      ASSERT_FAIL();
      return;
    }

    const glm::vec2& screenDimensions = getViewportDimensions();
    const glm::vec2& levelDimensions = screenBounds->findComponent<RectangleCollider>()->getDimensions();
    
    // Need to make map aspect ratio respect level bounds & screen size
    glm::vec2 mapSize = levelDimensions * 0.5f * glm::vec2(std::min(screenDimensions.x / levelDimensions.x, screenDimensions.y / levelDimensions.y));

    // Find all the spawn points and create the map UI
    if (screen->getUIManager().canAllocateImage())
    {
      const Handle<Image>& map = screen->getUIManager().allocateImage();
      createImage(map, Path("Sprites", "UI", "Rectangle.png"), Image::kFreeAspect, mapSize);
      addKeyboardVisibilityScript(map, GLFW_KEY_TAB, KeyboardVisibilityScript::kContinuous);

      map->getTransform()->setTranslation(glm::vec3(screenDimensions.x * 0.5f, screenDimensions.y * 0.5f, 0));
      map->setColour(0, 0, 0.5f, 0.5f);
      map->setShouldRender(false);

      for (const Handle<CelesteEngine::GameObject>& spawnPoint : screen->findGameObjectsWithTag("SpawnPoint"))
      {
        const Handle<Image>& spawnPointImage = screen->getUIManager().allocateImage();

        const glm::vec3 localTranslation = spawnPoint->getTransform()->getTranslation();
        float relativeX = (localTranslation.x * mapSize.x) / levelDimensions.x;
        float relativeY = (localTranslation.y * mapSize.y) / levelDimensions.y;

        spawnPointImage->getTransform()->setTranslation(relativeX, relativeY, 1);
        spawnPointImage->getTransform()->setParent(map->getTransform());

        // Parent first so that when we create the image, we take into account the parent's scale
        createImage(spawnPointImage, Path("Sprites", "Icons", "SpawnPoint.png"), Image::kPreserveAspect, glm::vec2(10, 10));
      }
    }

   /* Handle<GameObject> turret = screen->allocateAndInitializeGameObject();
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