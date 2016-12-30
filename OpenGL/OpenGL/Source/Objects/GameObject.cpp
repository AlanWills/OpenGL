#include "stdafx.h"

#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"


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

    if (findComponent<RectangleCollider>()->isMouseOver())
    {
      findComponent<SpriteRenderer>()->setColour(glm::vec4(1, 0, 0, 1));
    }
    else
    {
      findComponent<SpriteRenderer>()->setColour(glm::vec4(1, 1, 1, 1));
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