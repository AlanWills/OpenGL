#include "stdafx.h"

#include "Factories/ScreenFactory.h"
#include "Game/GameManager.h"
#include "Screens/MenuScreen.h"
#include "Resources/LoadResourcesAsyncScript.h"


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
    screen->addBackground("Logo");
    
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

    Handle<Button> exitGameButton = screen->getUIManager().allocateAndInitializeButton();
    exitGameButton->addOnLeftClickEvent(std::bind(&ScreenManager::exitCallback, GameManager::getScreenManager(), std::placeholders::_1));
    exitGameButton->getTransform()->translate(glm::vec3(GameManager::getScreenManager()->getViewportDimensions() * 0.5f, 0));

    return screen;
  }
}