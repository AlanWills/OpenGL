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
  void GameObject::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->initialize(component);
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

    std::vector<Handle<Component>> deadComponents;

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->update(secondsPerUpdate);

      if (!component->isAlive())
      {
        deadComponents.push_back(component);
      }
    }

    for (Handle<Component> component : deadComponents)
    {
      m_unmanagedComponents.erase(component);
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

    // Have to clear unmanaged components when we deallocate - we could be iterating over them when die is called.
  }
}