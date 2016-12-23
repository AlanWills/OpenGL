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
  void GameObject::awake()
  {
    Inherited::awake();

    for (Script* script : m_scripts)
    {
      script->awake();
    }
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

  //------------------------------------------------------------------------------------------------
  void GameObject::render(GLfloat lag)
  {
    Inherited::render(lag);

    for (Script* script : m_scripts)
    {
      script->render(lag);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::die()
  {
    Inherited::die();

    for (Component* component : m_components)
    {
      component->die();
    }

    m_components.clear();
    m_scripts.clear();
  }
}