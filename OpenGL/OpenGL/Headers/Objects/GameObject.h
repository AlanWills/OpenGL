#pragma once

#include "Scripts/Script.h"
#include "Maths/Transform.h"

#include <vector>


namespace OpenGL
{
class GameObject : public Component
{
  public:
    GameObject();
    virtual ~GameObject();

    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

    const Transform& getConstTransform() const { return m_transform; }
    Transform& getTransform() { return m_transform; }

    StringId getName() const { return m_name; }

    /// \brief Inserts the inputted component into the components associated with this game object
    template <typename T>
    Handle<T> addComponent(Handle<T> component);

  protected:
    Transform m_transform;

  private:
    typedef Component Inherited;

    StringId m_name;

    std::vector<Handle<Component>> m_components;
    std::vector<Handle<Script>> m_scripts;
};

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T> GameObject::addComponent(Handle<T> component)
{
  if (!component.get())
  {
    ASSERT_FAIL_MSG("Component is nullptr");
    return nullptr;
  }

  if (component.is<Script>())
  {
    // If we have a script we need to add it to the scripts list instead - this is because they are updated by the objects they are assigned to
    m_scripts.push_back(component.as<Script>());
  }
  else
  {
    m_components.push_back(component.as<Component>());
  }

  return component;
}

}