#pragma once

#include "GLHeaders.h"
#include "Memory/ComponentAllocator.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT(ComponentType, PoolSize) \
public: \
  static bool canAllocate() { return m_componentAllocator.canAllocate(); } \
  \
  static ComponentType* allocate() \
  { \
    ASSERT(m_componentAllocator.canAllocate()); \
    return m_componentAllocator.allocate(); \
  } \
  \
  static ComponentType* allocateAndInitialize() \
  { \
    ASSERT(m_componentAllocator.canAllocate()); \
    ComponentType* component = m_componentAllocator.allocate(); \
    component->initialize(); \
    return component; \
  } \
private: \
  typedef ComponentAllocator<ComponentType, PoolSize> Allocator; \
  static Allocator m_componentAllocator;

//------------------------------------------------------------------------------------------------
#define REGISTER_COMPONENT(ComponentType) \
ComponentType::Allocator ComponentType::m_componentAllocator = ComponentType::Allocator();

class Component
{
  public:
    Component();
    virtual ~Component();

    /// \brief Sets the object to be alive
    virtual void initialize();
    virtual void awake();
    virtual void handleInput(GLfloat elapsedGameTime) {}
    virtual void update(GLfloat secondsPerUpdate);
    virtual void render(GLfloat lag) {}
    virtual void die();

    bool isAlive() const { return m_alive; }

  private:
    bool m_alive;
    bool m_initialized;
    bool m_awake;
};

}