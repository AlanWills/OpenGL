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
    T* addComponent(T* component);

  protected:
    Transform m_transform;

  private:
    typedef Component Inherited;

    StringId m_name;

    std::vector<Component*> m_components;
    std::vector<Script*> m_scripts;
};

//------------------------------------------------------------------------------------------------
template <typename T>
T* GameObject::addComponent(T* component)
{
  if (!component)
  {
    ASSERT_FAIL_MSG("Component is nullptr");
    return nullptr;
  }

  // If we have a script we need to add it to the scripts list instead
  Script* script = dynamic_cast<Script*>(component);
  if (script)
  {
    m_scripts.push_back(script);
  }
  else
  {
    m_components.push_back(component);
  }

  return component;
}

}