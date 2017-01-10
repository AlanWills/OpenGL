#pragma once

#include "Objects/UIObject.h"


namespace OpenGL
{

/// A class which is responsible for arranging elements either vertically or horizontally,
/// so that they are distributed evenly about the centre of this panel
/// The panel will automatically adjust the positions of it's children UIObjects when a new child UIObject is added to preserve a symmetrical layout
class StackPanel : public UIObject
{
  public:
    StackPanel();
    virtual ~StackPanel();

    template <ManagementType MType, typename T>
    void addComponent(Handle<T> component) override;

  private:
    typedef UIObject Inherited;

    void calculateLayout();

    // All of the UIObjects that have been added to this stack panel
    std::vector<Handle<UIObject>> m_children;
};

//------------------------------------------------------------------------------------------------
template <ManagementType MType, typename T>
void StackPanel::addComponent(Handle<T> component)
{
  Inherited::addComponent(component);

  if (component.is<UIObject>())
  {
    m_children.push_back(component.as<UIObject>());
  }
}

}