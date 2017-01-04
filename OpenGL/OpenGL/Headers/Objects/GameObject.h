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
    virtual ~GameObject();

    void initialize(Handle<Component> allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

    Transform& getTransform() { return m_transform; }
    const Transform& getTransform() const { return m_transform; }

    StringId getName() const { return m_name; }

    /// \brief Inserts the inputted component into the components associated with this game object
    template <ManagementType MType, typename T>
    Handle<T> addComponent(Handle<T> component);

    template <typename T>
    Handle<T> findComponent() const;

  protected:
    Transform m_transform;

  private:
    typedef Component Inherited;

    StringId m_name;

    std::vector<Handle<Component>> m_managedComponents;
    std::vector<Handle<Component>> m_unmanagedComponentsToAdd;
    std::vector<Handle<Component>> m_unmanagedComponentsToRemove;
    std::unordered_set<Handle<Component>> m_unmanagedComponents;
};

//------------------------------------------------------------------------------------------------
template <ManagementType MType, typename T>
Handle<T> GameObject::addComponent(Handle<T> component)
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

}