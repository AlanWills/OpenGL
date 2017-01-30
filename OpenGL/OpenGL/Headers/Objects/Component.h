#pragma once

#include "OpenGL/GLHeaders.h"
#include "Memory/ComponentAllocator.h"
#include "Memory/PoolAllocator.h"
#include "Memory/GapAllocator.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT(AllocatorType, ComponentType, PoolSize) \
public: \
  static bool canAllocate() { return m_componentAllocator.canAllocate(); } \
  \
  static Handle<ComponentType> allocateAndInitialize() \
  { \
    ASSERT(m_componentAllocator.canAllocate()); \
    return m_componentAllocator.allocateAndInitialize(); \
  } \
  \
  ComponentType(); \
  ~ComponentType(); \
  \
private: \
  typedef ComponentAllocator<AllocatorType<ComponentType, PoolSize>, ComponentType, PoolSize> Alloc; \
  static Alloc m_componentAllocator;

//------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT_WITH_MANAGER(AllocatorType, ComponentType, PoolSize, Manager) \
  DECLARE_COMPONENT(AllocatorType, ComponentType, PoolSize); \
  private: \
    friend class Manager;

//------------------------------------------------------------------------------------------------
#define REGISTER_COMPONENT(ComponentType) \
  ComponentType::Alloc ComponentType::m_componentAllocator = ComponentType::Alloc();

#define DECLARE_CLASS_COMPONENT(ComponentType, MemberName) \
  private: \
    ComponentType MemberName; \
    ComponentType* MemberName##Ptr = &MemberName;

#define ADD_AND_INITIALIZE_CLASS_COMPONENT(ComponentType, MemberName) \
  { \
    Handle<ComponentType> component = Handle<ComponentType>(&MemberName##Ptr); \
    addComponent<kUnmanaged>(component); \
    component->initialize(component); \
  }

#define DECLARE_CLASS_COMPONENT_ALLOCATOR(ComponentType, PoolSize, MemberName) \
  public: \
    bool canAllocate##ComponentType() const { return MemberName##.canAllocate(); } \
    \
    Handle<ComponentType> allocateAndInitialize##ComponentType() \
    { \
      ASSERT(canAllocate##ComponentType##()); \
      return MemberName##.allocateAndInitialize(); \
    } \
  private: \
    ComponentAllocator<PoolAllocator<ComponentType, PoolSize>, ComponentType, PoolSize> MemberName;

class GameObject;

class Component
{
  public:
    Component();
    virtual ~Component();

    /// \brief Sets the object to be alive and sets it's allocator handle to the inputted value
    virtual void initialize(const Handle<Component>& allocHandle);
    virtual void awake();
    virtual void handleInput(GLfloat elapsedGameTime) {}
    virtual void update(GLfloat secondsPerUpdate);
    virtual void render(GLfloat lag) {}
    virtual void die();

    bool isAlive() const { return m_alive; }
    bool isAwake() const { return m_awake; }

    const Handle<Component>& getAllocatorHandle() const { return m_allocatorHandle; }
    const Handle<GameObject>& getParent() const { return m_owner; }

    // Don't like this, but can't think of an alternative right now
    void setParent(const Handle<GameObject>& gameObject);

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