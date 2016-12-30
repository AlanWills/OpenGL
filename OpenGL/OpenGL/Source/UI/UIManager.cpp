#include "stdafx.h"

#include "UI/UIManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  UIManager::UIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  UIManager::~UIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::awake()
  {
    Inherited::awake();
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::render(GLfloat lag)
  {
    Inherited::render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void UIManager::die()
  {
    Inherited::die();
  }
}