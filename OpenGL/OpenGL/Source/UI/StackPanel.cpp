#include "stdafx.h"

#include "UI/StackPanel.h"
#include "Rendering/Renderer.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  StackPanel::StackPanel() :
    m_orientation(kVertical),
    m_padding(5)
  {
  }

  //------------------------------------------------------------------------------------------------
  StackPanel::~StackPanel()
  {
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::addChild(Handle<UIObject> uiObject)
  {
    // We use the renderers to calculate the bounds of an object for layout
    ASSERT(uiObject->hasComponent<Renderer>());

    uiObject->getTransform()->setParent(getTransform());
    m_children.push_back(uiObject);

    layout();
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::layout()
  {
    // Iterate over all items and arrange them accordingly
    glm::vec2 totalSize;

    for (Handle<UIObject> child : m_children)
    {
      ASSERT(child->hasComponent<Renderer>());
      totalSize += child->findComponent<Renderer>()->getDimensions();
    }

    totalSize += (float)(m_children.size() - 1) * glm::vec2(m_padding);

    if (m_orientation == kHorizontal)
    {
      // Stack all the children horizontally with the first added on the left
      float currentLeft = -totalSize.x * 0.5f;

      for (Handle<UIObject> child : m_children)
      {
        Handle<Renderer> renderer = child->findComponent<Renderer>();
        float halfWidth = renderer->getDimensions().x * 0.5f;

        if (child != m_children.front())
        {
          currentLeft += m_padding * 0.5f;
        }

        child->getTransform()->setLocalTranslation(glm::vec3(currentLeft + halfWidth, 0, 0));

        currentLeft += 2 * halfWidth;

        if (child != m_children.back())
        {
          currentLeft += m_padding * 0.5f;
        }
      }
    }
    else
    {
      // Stack all the children vertically with the first added at the top
      float currentTop = totalSize.y * 0.5f;

      for (Handle<UIObject> child : m_children)
      {
        Handle<Renderer> renderer = child->findComponent<Renderer>();
        float halfHeight = renderer->getDimensions().y * 0.5f;

        if (child != m_children.front())
        {
          currentTop -= m_padding * 0.5f;
        }

        child->getTransform()->setLocalTranslation(glm::vec3(0, currentTop - halfHeight, 0));

        currentTop -= 2 * halfHeight;

        if (child != m_children.back())
        {
          currentTop -= m_padding * 0.5f;
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::die()
  {
    m_children.clear();
  }
}