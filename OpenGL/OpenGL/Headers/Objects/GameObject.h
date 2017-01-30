#pragma once

#include "Scripts/Script.h"
#include "Maths/Transform.h"

#include <vector>
#include <unordered_set>


namespace OpenGL
{

enum ManagementType
{
  kManaged,
  kUnmanaged
};

class GameObject : public Component
{
  public:
    GameObject();
    ~GameObject();

    void initialize(const Handle<Component>& allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

    const Handle<Transform>& getTransform() { return m_transform; }
    const Handle<Transform>& getTransform() const { return m_transform; }

    void setName(const std::string& name) { m_name = internString(name); }
    void setName(StringId name) { m_name = name; }
    StringId getName() const { return m_name; }

    /// \brief Inserts the inputted component into the components associated with this game object
    template <ManagementType MType, typename T>
    const Handle<T>& addComponent(const Handle<T>& component);

    template <typename T>
    Handle<T> findComponent() const;

    template <typename T>
    bool hasComponent() const;

  private:
    typedef Component Inherited;

    Handle<Transform> m_transform;

    StringId m_name;

    std::vector<Handle<Component>> m_managedComponents;
    std::vector<Handle<Component>> m_unmanagedComponentsToAdd;
    std::vector<Handle<Component>> m_unmanagedComponentsToRemove;
    std::unordered_set<Handle<Component>> m_unmanagedComponents;
};

//------------------------------------------------------------------------------------------------
template <ManagementType MType, typename T>
const Handle<T>& GameObject::addComponent(const Handle<T>& component)
{
  if (!component.get())
  {
    ASSERT_FAIL_MSG("Component is nullptr");
    return nullptr;
  }

  if (MType == kUnmanaged)
  {
    // Add to the unmanaged set
    m_unmanagedComponentsToAdd.push_back(component);
  }
  else
  {
    m_managedComponents.push_back(component);
  }

  component->setParent(getAllocatorHandle().as<GameObject>());

  return component;
}

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T> GameObject::findComponent() const
{
  for (const Handle<Component>& handle : m_managedComponents)
  {
    if (handle.is<T>())
    {
      return handle.as<T>();
    }
  }

  for (const Handle<Component>& handle : m_unmanagedComponents)
  {
    if (handle.is<T>())
    {
      return handle.as<T>();
    }
  }

  for (const Handle<Component>& handle : m_unmanagedComponentsToAdd)
  {
    if (handle.is<T>())
    {
      return handle.as<T>();
    }
  }

  ASSERT_FAIL();
  return Handle<T>(nullptr);
}

//------------------------------------------------------------------------------------------------
template <typename T>
bool GameObject::hasComponent() const
{
  for (const Handle<Component>& handle : m_managedComponents)
  {
    if (handle.is<T>())
    {
      return true;
    }
  }

  for (const Handle<Component>& handle : m_unmanagedComponents)
  {
    if (handle.is<T>())
    {
      return true;
    }
  }

  for (const Handle<Component>& handle : m_unmanagedComponentsToAdd)
  {
    if (handle.is<T>())
    {
      return true;
    }
  }

  return false;
}

}