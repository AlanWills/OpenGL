#include "stdafx.h"

#include "Factories/ScreenFactory.h"
#include "Resources/LoadResourcesAsyncScript.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Handle<Screen> ScreenFactory::createStartupLogoScreen() const
  {
    if (!Screen::canAllocate())
    {
      ASSERT_FAIL();
      return Handle<Screen>();
    }

    Handle<Screen> screen = Screen::allocateAndInitialize();

    if (!screen->canAllocateGameObject())
    {
      ASSERT_FAIL();
      return Handle<Screen>();
    }

    Handle<GameObject> resourceLoader = screen->allocateAndInitializeGameObject();
    resourceLoader->addComponent<kManaged>(LoadResourcesAsyncScript::allocateAndInitialize());
    
    return screen;
  }
}