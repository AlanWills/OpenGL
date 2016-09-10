#pragma once

#include "Component.h"
#include <vector>
#include <memory>

class GameObject
{

public:
  GameObject();
  ~GameObject();

  void update();
  void draw(GLfloat elapsedTime);

  /// \brief Add a component to this object
  /// This object will always take ownership of the inputted component
  void addComponent(const std::unique_ptr<Component>& component);
  void addComponent(Component* component);

private:
  std::vector<std::unique_ptr<Component>> m_components;
};

