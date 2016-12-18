#pragma once

#include "Component.h"
#include "Rendering/SpriteRenderer.h"
#include "Maths/Transform.h"

#include <vector>


namespace OpenGL
{
  class GameObject : public Component
  {
    public:
      GameObject();
      virtual ~GameObject();

      const Transform& getConstTransform() const { return m_transform; }
      Transform& getTransform() { return m_transform; }

      StringId getName() const { return m_name; }

      /// \brief Inserts the inputted component into the components associated with this game object
      void addComponent(Component* component) { m_components.push_back(component); }

    private:
      Transform m_transform;
      StringId m_name;

      std::vector<Component*> m_components;
  };
}