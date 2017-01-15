#include "stdafx.h"

#include "Objects/GameObject.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  GameObject::GameObject() :
    m_transform(nullptr),
    m_name(-1)
  {
  }

  //------------------------------------------------------------------------------------------------
  GameObject::~GameObject()
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::initialize(const Handle<Component>& allocHandle)
  {
    Inherited::initialize(allocHandle);

    ASSERT(Transform::canAllocate());
    m_transform = Transform::allocate();

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->initialize(component);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::awake()
  {
    Inherited::awake();

    for (Handle<Component> component : m_unmanagedComponentsToAdd)
    {
      m_unmanagedComponents.insert(component);
    }

    m_unmanagedComponentsToAdd.clear();

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->awake();
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

    for (Handle<Component> component : m_unmanagedComponentsToAdd)
    {
      m_unmanagedComponents.insert(component);
    }

    m_unmanagedComponentsToAdd.clear();

    for (Handle<Component> component : m_unmanagedComponents)
    {
      component->update(secondsPerUpdate);

      if (!component->isAlive())
      {
        m_unmanagedComponentsToRemove.push_back(component);
      }
    }

    for (Handle<Component> component : m_unmanagedComponentsToRemove)
    {
      m_unmanagedComponents.erase(component);
    }

    m_unmanagedComponentsToRemove.clear();
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

    Transform::deallocate(m_transform);

    // Have to clear unmanaged components when we deallocate - we could be iterating over them when die is called.
  }
}