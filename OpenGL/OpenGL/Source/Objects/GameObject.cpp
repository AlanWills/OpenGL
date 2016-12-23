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

    for (Handle<Script> script : m_scripts)
    {
      script->awake();
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    for (Handle<Script> script : m_scripts)
    {
      script->handleInput(elapsedGameTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    for (Handle<Script> script : m_scripts)
    {
      script->update(secondsPerUpdate);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::render(GLfloat lag)
  {
    Inherited::render(lag);

    for (Handle<Script> script : m_scripts)
    {
      script->render(lag);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::die()
  {
    Inherited::die();

    for (Handle<Component> component : m_components)
    {
      component->die();
    }

    m_components.clear();
    m_scripts.clear();
  }
}