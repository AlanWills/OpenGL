#pragma once

#include "Objects/UIObject.h"
#include "Rendering/SpriteRenderer.h"


namespace OpenGL
{

class Image : public UIObject
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, Image, 10, UIManager);

  public:
    void initialize(Handle<Component> allocHandle) override;

    void setImage(const std::string& image) { m_spriteRenderer.setTexture(image); }

    /// \brief Scales the image but will maintain it's aspect ratio
    void setSize(const glm::vec2& size);

  private:
    typedef UIObject Inherited;

    DECLARE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer)
};

}