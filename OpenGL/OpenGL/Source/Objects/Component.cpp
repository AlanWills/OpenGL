#include "stdafx.h"

#include "Objects/Component.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Component::Component() :
    m_alive(false),
    m_initialized(false),
    m_awake(false)
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
  void Component::awake()
  {
    ASSERT(m_initialized);
    ASSERT(!m_awake);

    m_awake = true;
  }

  //------------------------------------------------------------------------------------------------
  void Component::update(GLfloat secondsPerUpdate)
  {
    if (!m_awake)
    {
      awake();
      ASSERT(m_awake);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Component::die()
  {
    ASSERT(m_alive);
    ASSERT(m_initialized);
    ASSERT(m_awake);

    m_alive = false;
    m_initialized = true;
    m_awake = false;
  }
}