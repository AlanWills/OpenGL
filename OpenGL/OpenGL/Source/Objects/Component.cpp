#include "stdafx.h"

#include "Objects/Component.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Component::Component() :
    m_alive(false),
    m_initialized(false),
    m_begun(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  Component::~Component()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Component::initialize()
  {
    // Check that this object is not currently alive
    ASSERT(!m_alive);
    m_alive = true;

    // Check we haven't already called initialize
    ASSERT(!m_initialized);
    m_initialized = true;
  }

  //------------------------------------------------------------------------------------------------
  void Component::begin()
  {
    ASSERT(m_initialized);
    ASSERT(!m_begun);

    m_begun = true;
  }

  //------------------------------------------------------------------------------------------------
  void Component::update(GLfloat secondsPerUpdate)
  {
    if (!m_begun)
    {
      begin();
      ASSERT(m_begun);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Component::die()
  {
    ASSERT(m_alive);
    ASSERT(m_initialized);
    ASSERT(m_begun);

    m_alive = false;
    m_initialized = true;
    m_begun = false;
  }
}