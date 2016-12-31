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
    return m_componentAllocator.allocateAndInitialize(); \
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

#define DECLARE_CLASS_COMPONENT(ComponentType, MemberName) \
  private: \
    ComponentType MemberName; \
    ComponentType* MemberName##Ptr = &MemberName;

#define ADD_CLASS_COMPONENT(ComponentType, MemberName) \
  addComponent<kUnmanaged>(Handle<ComponentType>(&MemberName##Ptr));

#define DECLARE_CLASS_COMPONENT_ALLOCATOR(ComponentType, PoolSize, MemberName) \
  public: \
    bool canAllocate##ComponentType() const { return MemberName##.canAllocate(); } \
    \
    Handle<ComponentType> allocate##ComponentType() \
    { \
      ASSERT(canAllocate##ComponentType##()); \
      return MemberName##.allocate(); \
    } \
    \
    Handle<ComponentType> allocateAndInitialize##ComponentType() \
    { \
      ASSERT(canAllocate##ComponentType##()); \
      return MemberName##.allocateAndInitialize(); \
    } \
  private: \
    ComponentAllocator<ComponentType, PoolSize> MemberName;

class GameObject;

class Component
{
  public:
    Component();
    virtual ~Component();

    /// \brief Sets the object to be alive and sets it's allocator handle to the inputted value
    virtual void initialize(Handle<Component> allocHandle);
    virtual void awake();
    virtual void handleInput(GLfloat elapsedGameTime) {}
    virtual void update(GLfloat secondsPerUpdate);
    virtual void render(GLfloat lag) {}
    virtual void die();

    bool isAlive() const { return m_alive; }

    Handle<Component> getAllocatorHandle() const { return m_allocatorHandle; }
    Handle<GameObject> getOwner() const { return m_owner; }

    // Don't like this, but can't think of an alternative right now
    void setOwner(Handle<GameObject> gameObject);

  private:
    bool m_alive;
    bool m_initialized;
    bool m_awake;

    /// \brief The handle of this component in it's custom allocator
    /// \brief Potentially a nullptr handle if it is not allocated in a custom way
    Handle<Component> m_allocatorHandle;

    /// \brief The handle of the game object which owns this component
    /// (Only class which inherited from GameObject can have components)
    Handle<GameObject> m_owner;
};

}