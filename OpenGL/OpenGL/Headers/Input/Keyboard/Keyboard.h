#pragma once

#include "GLHeaders.h"

namespace OpenGL
{

#define KEYBOARD_KEY_COUNT 1024

class Keyboard
{
  public:
    Keyboard();
    virtual ~Keyboard();

    void update(GLfloat elapsedGameTime);

    void setKeyDown(int key);
    void setKeyUp(int key);

    virtual GLboolean isKeyDown(int key) const;
    virtual GLboolean isKeyPressed(int key) const;

    /// \brief Sets every value of the current keys to GL_FALSE so that
    /// all calls to isKeyDown and isKeyPressed will return GL_FALSE;
    void flush();

  private:
    int m_currentKeys[KEYBOARD_KEY_COUNT];
    int m_previousKeys[KEYBOARD_KEY_COUNT];
};

}