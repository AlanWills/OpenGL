#pragma once

#include "OpenGL/GLHeaders.h"
#include "Memory/GapAllocator.h"


namespace OpenGL
{

/// A class representing a transformation in 3D space with various utility functions for manipulation and hierarchy.
class Transform
{
  public:
    static bool canAllocate() { return m_allocator.canAllocate(); }

    static Handle<Transform> allocate()
    {
      ASSERT(m_allocator.canAllocate());
      return m_allocator.allocate();
    }

    static void deallocate(Handle<Transform> item) 
    { 
      // Reset the transform when we deallocate
      item->setLocalMatrix(glm::mat4());
      item->setParent(Handle<Transform>());

      m_allocator.deallocate(item.get()); 
    }

    Transform(glm::mat4 localMatrix = glm::mat4());

    glm::mat4 getWorldMatrix() const { return m_parent.get() ? m_localMatrix * m_parent->getWorldMatrix() : m_localMatrix; }
    glm::vec3 getWorldTranslation() const;

    const glm::mat4& getLocalMatrix() const { return m_localMatrix; }
    void setLocalMatrix(const glm::mat4& localMatrix) { m_localMatrix = localMatrix; }

    void applyTransform(const glm::mat4& transform) { m_localMatrix *= transform; }
      
    void translate(const glm::vec2& translation);
    void translate(const glm::vec3& translation);

    void setLocalTranslation(const glm::vec3& translation);
    glm::vec3 getLocalTranslation() const;

    void setParent(Handle<Transform> parent) { m_parent = parent; }

  private:
    typedef GapAllocator<Transform, 10> Alloc; \
    static Alloc m_allocator;

    Handle<Transform> m_parent;
    glm::mat4 m_localMatrix;
};

}