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
      item->setRotation(0);
      item->setTranslation(glm::zero<glm::vec3>());
      item->setScale(glm::one<glm::vec3>());
      item->setParent(Handle<Transform>());

      m_allocator.deallocate(item.get()); 
    }

    Transform(glm::mat4 localMatrix = glm::mat4());

    void setParent(Handle<Transform> parent) { m_parent = parent; }

    glm::mat4 getWorldMatrix() const;
    glm::vec3 getWorldTranslation() const;
    glm::vec3 getWorldScale() const;
    float getWorldRotation() const;

    glm::mat4 getLocalMatrix() const;

    void rotate(float deltaRotation) { m_rotation += deltaRotation; }
    void setRotation(float rotation) { m_rotation = rotation; }
    float getRotation() const { return m_rotation; }

    void translate(float x, float y) { translate(x, y, 0); }
    void translate(const glm::vec2& translation) { translate(glm::vec3(translation, 0)); }
    void translate(float x, float y, float z) { translate(glm::vec3(x, y, z)); }
    void translate(const glm::vec3& translation) { m_translation += translation; }
    void setTranslation(const glm::vec3& translation) { m_translation = translation; }
    const glm::vec3& getTranslation() const { return m_translation; }

    void scale(const glm::vec2& scalingFactor) { scale(glm::vec3(scalingFactor, 1)); }
    void scale(const glm::vec3& scalingFactor) { m_scale *= scalingFactor; }
    void setScale(const glm::vec3& scale) { m_scale = scale; }
    const glm::vec3& getScale() const { return m_scale; }

  private:
    typedef GapAllocator<Transform, 10> Alloc; \
    static Alloc m_allocator;

    Handle<Transform> m_parent;

    float m_rotation;
    glm::vec3 m_translation;
    glm::vec3 m_scale;
};

}