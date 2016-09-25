#pragma once

#include "DllExport.h"
#include <array>

namespace Engine
{
  #define KEYBOARD_KEY_COUNT 1024

class DllExport Keyboard
{
  public:
    Keyboard();
    virtual ~Keyboard();

    void update(GLfloat elapsedGameTime);

    void setKeyDown(int key);
    void setKeyUp(int key);

    virtual GLboolean isKeyDown(int key) const;
    virtual GLboolean isKeyPressed(int key) const;

protected:
  typedef std::array<int, KEYBOARD_KEY_COUNT> KeyArray;

private:
    KeyArray m_currentKeys;
    KeyArray m_previousKeys;
};

}