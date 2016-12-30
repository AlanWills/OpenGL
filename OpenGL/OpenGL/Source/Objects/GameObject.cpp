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
  void GameObject::initialize()
  {
    Inherited::initialize();

    for (Handle<Component> script : m_unmanagedComponents)
    {
      script->initialize();
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::awake()
  {
    Inherited::awake();

    for (Handle<Component> script : m_unmanagedComponents)
    {
      script->awake();
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->handleInput(elapsedGameTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->update(secondsPerUpdate);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::render(GLfloat lag)
  {
    Inherited::render(lag);

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->render(lag);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::die()
  {
    Inherited::die();

    for (Handle<Component> component : m_managedComponents)
    {
      component->die();
    }

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->die();
    }

    m_managedComponents.clear();
    m_unmanagedComponents.clear();
  }
}