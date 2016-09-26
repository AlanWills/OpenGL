#pragma once

#include "DllExport.h"
#include "GLHeaders.h"

namespace Engine
{

class DllExport Mouse
{
  public:
    Mouse();
    virtual ~Mouse();

    void update(GLfloat elapsedGameTime);

    enum MouseButton
    {
      kLeft,
      kMiddle,
      kRight,
      kNumButtons,
    };

    void setButtonDown(MouseButton mouseButton);
    void setButtonUp(MouseButton mouseButton);

    /// \brief Returns true if the inputted mouse button is down this frame
    virtual GLboolean isButtonDown(MouseButton mouseButton) const;

    /// \brief Returns true if the inputted mouse button is down last frame and up this frame
    /// It's possible we should reverse this logic - we shall see how it feels in game
    virtual GLboolean isButtonPressed(MouseButton mouseButton) const;

    void flush();

  private:
    GLboolean m_currentButtons[MouseButton::kNumButtons];
    GLboolean m_previousButtons[MouseButton::kNumButtons];
};

};