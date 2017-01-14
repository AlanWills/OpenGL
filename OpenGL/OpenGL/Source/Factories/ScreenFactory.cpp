#include "stdafx.h"

#include "Factories/ScreenFactory.h"
#include "Game/GameManager.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Audio/AudioSource.h"


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
  Handle<Screen> ScreenFactory::createSplashScreen() const
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
  Handle<Screen> ScreenFactory::createMainMenuScreen() const
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
    playGameButton->setText("Play");

    Handle<Button> exitGameButton = screen->getUIManager().allocateAndInitializeButton();
    exitGameButton->addOnLeftClickEvent(std::bind(&ScreenManager::exitCallback, GameManager::getScreenManager(), std::placeholders::_1));
    exitGameButton->setText("Exit");

    buttonStackPanel->addChild(playGameButton);
    buttonStackPanel->addChild(exitGameButton);

    return screen;
  }


  //------------------------------------------------------------------------------------------------
  void ScreenFactory::addScreenBackground(const Handle<Screen>& screen, const std::string& backgroundImage) const
  {
    const glm::vec2& screenDimensions = GameManager::getScreenManager()->getViewportDimensions();

    Handle<Image> image = screen->getUIManager().allocateAndInitializeImage();
    image->setImage(backgroundImage);
    image->setSize(screenDimensions);
    image->getTransform()->translate(screenDimensions * 0.5f);
  }
}