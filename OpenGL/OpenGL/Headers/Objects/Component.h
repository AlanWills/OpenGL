#pragma once

#include "OpenGL/GLHeaders.h"
#include "Memory/ComponentAllocator.h"


namespace OpenGL
{
//------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT(ComponentType, PoolSize) \
public: \
  static bool canAllocate() { return m_componentAllocator.canAllocate(); } \
  \
  static Handle<ComponentType> allocate() \
  { \
    ASSERT(m_componentAllocator.canAllocate()); \
    return m_componentAllocator.allocate(); \
  } \
  \
  static Handle<ComponentType> allocateAndInitialize() \
  { \
    ASSERT(m_componentAllocator.canAllocate()); \
    Handle<ComponentType> component = m_componentAllocator.allocate(); \
    component->initialize(); \
    return component; \
  } \
  \
  ComponentType(); \
  virtual ~ComponentType(); \
  \
private: \
  typedef ComponentAllocator<ComponentType, PoolSize> Allocator; \
  static Allocator m_componentAllocator;

//------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT_WITH_MANAGER(ComponentType, PoolSize, Manager) \
  DECLARE_COMPONENT(ComponentType, PoolSize); \
  private: \
    friend class Manager;

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