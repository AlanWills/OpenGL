#pragma once

#include "GLHeaders.h"


namespace OpenGL
{
  class Component
  {
    public:
      Component();
      virtual ~Component();

      /// \brief Sets the object to be alive
      virtual void initialize();
      virtual void begin();
      virtual void handleInput(GLfloat elapsedGameTime) {}
      virtual void update(GLfloat elapsedGameTime);
      virtual void render(GLfloat lag) {}
      virtual void die();

      bool isAlive() const { return m_alive; }

    private:
      bool m_alive;
      bool m_initialized;
      bool m_begun;
  };
}