#include "stdafx.h"

#include "Objects/Component.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Component::Component() :
    m_alive(false),
    m_initialized(false),
    m_awake(false),
    m_allocatorHandle(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  Component::~Component()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Component::initialize(Handle<Component> allocHandle)
  {
    m_allocatorHandle = allocHandle;

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

  //------------------------------------------------------------------------------------------------
  void Component::setOwner(Handle<GameObject> owner)
  {
    if (!owner.get() ||
         m_owner.get())
    {
      // Don't want to set the owner to nullptr or set it again if we have already set it
      ASSERT_FAIL();
      return;
    }

    m_owner = owner;
  }
}