#include "stdafx.h"

#include "Factories/ScreenFactory.h"
#include "Game/GameManager.h"
#include "Screens/MenuScreen.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "Audio/AudioSource.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::createStartupLogoScreen() const
  {
    Handle<MenuScreen> screen = allocateScreenAndTransition<MenuScreen>();

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return Handle<Screen>();
    }

    // Attach the async resource loader to a game object
    Handle<GameObject> resourceLoader = screen->allocateAndInitializeGameObject();
    resourceLoader->addComponent<kUnmanaged>(LoadResourcesAsyncScript::allocateAndInitialize());

    // Add a background image
    screen->addBackground("Logo.png");
    
    return screen;
  }

  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::createMainMenuScreen() const
  {
    Handle<MenuScreen> screen = allocateScreenAndTransition<MenuScreen>();

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
}