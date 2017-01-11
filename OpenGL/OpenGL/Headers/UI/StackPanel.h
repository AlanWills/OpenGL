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

    enum Orientation
    {
      kHorizontal,
      kVertical,
    };

    void die() override;

    void addChild(Handle<UIObject> uiObject);

    void setOrientation(Orientation orientation) { m_orientation = orientation; }
    void setPadding(float padding) { m_padding = padding; }

  private:
    typedef UIObject Inherited;

    /// \brief Position all the added children to create a symmetric distribution
    void layout();

    // All of the UIObjects that have been added to this stack panel
    std::vector<Handle<UIObject>> m_children;

    /// \brief The direction around which we will stack the children
    Orientation m_orientation;

    /// \brief The padding we apply between successive elements
    float m_padding;
};

}