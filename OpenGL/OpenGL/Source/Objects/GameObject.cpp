#include "stdafx.h"

#include "Objects/GameObject.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  GameObject::GameObject() :
    m_transform(),
    m_name(-1)
  {
  }

  //------------------------------------------------------------------------------------------------
  GameObject::~GameObject()
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    for (Script* script : m_scripts)
    {
      script->handleInput(elapsedGameTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    for (Script* script : m_scripts)
    {
      script->update(secondsPerUpdate);
    }
  }
}