#include "GameObject.h"

//------------------------------------------------------------------------------------------------
GameObject::GameObject()
{
}

//------------------------------------------------------------------------------------------------
GameObject::~GameObject()
{
}

//------------------------------------------------------------------------------------------------
void GameObject::update()
{
  for (const std::unique_ptr<Component>& component : m_components)
  {
    component->update();
  }
}

//------------------------------------------------------------------------------------------------
void GameObject::draw(GLfloat percentageIntoFrame)
{
  for (const std::unique_ptr<Component>& component : m_components)
  {
    component->draw(percentageIntoFrame);
  }
}

//------------------------------------------------------------------------------------------------
void GameObject::addComponent(const std::unique_ptr<Component>& component)
{
  //m_components.emplace_back(component);
}

//------------------------------------------------------------------------------------------------
void GameObject::addComponent(Component* component)
{
  m_components.emplace_back(component);
}