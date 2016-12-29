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
private: \
  typedef ComponentAllocator<ComponentType, PoolSize> Allocator; \
  static Allocator m_componentAllocator;

//------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT_WITH_MANAGER(ComponentType, PoolSize, Manager) \
  DECLARE_COMPONENT(ComponentType, PoolSize); \
  private: \
    friend class Manager;

//------------------------------------------------------------------------------------------------
#define DECLARE_SCREEN_AND_WORLD_COMPONENT(ComponentType, PoolSize) \
public: \
  static bool canAllocateWorld() { return m_worldAllocator.canAllocate(); } \
  static bool canScreenWorld() { return m_screenAllocator.canAllocate(); } \
  \
  static Handle<ComponentType> allocateWorld() \
  { \
    ASSERT(m_worldAllocator.canAllocate()); \
    return m_worldAllocator.allocate(); \
  } \
  \
  static Handle<ComponentType> allocateScreen() \
  { \
    ASSERT(m_screenAllocator.canAllocate()); \
    return m_screenAllocator.allocate(); \
  } \
  \
  static Handle<ComponentType> allocateWorldAndInitialize() \
  { \
    ASSERT(m_worldAllocator.canAllocate()); \
    Handle<ComponentType> component = m_worldAllocator.allocate(); \
    component->initialize(); \
    return component; \
  } \
  static Handle<ComponentType> allocateScreenAndInitialize() \
  { \
    ASSERT(m_screenAllocator.canAllocate()); \
    Handle<ComponentType> component = m_screenAllocator.allocate(); \
    component->initialize(); \
    return component; \
  } \
private: \
  typedef ComponentAllocator<ComponentType, PoolSize> Allocator; \
  static Allocator m_screenAllocator; \
  static Allocator m_worldAllocator;

//------------------------------------------------------------------------------------------------
#define DECLARE_SCREEN_AND_WORLD_COMPONENT_WITH_MANAGER(ComponentType, PoolSize, Manager) \
  DECLARE_SCREEN_AND_WORLD_COMPONENT(ComponentType, PoolSize); \
  private: \
    friend class Manager;

//------------------------------------------------------------------------------------------------
#define REGISTER_COMPONENT(ComponentType) \
ComponentType::Allocator ComponentType::m_componentAllocator = ComponentType::Allocator();

//------------------------------------------------------------------------------------------------
#define REGISTER_WORLD_AND_SCREEN_COMPONENT(ComponentType) \
ComponentType::Allocator ComponentType::m_worldAllocator = ComponentType::Allocator(); \
ComponentType::Allocator ComponentType::m_screenAllocator = ComponentType::Allocator();


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