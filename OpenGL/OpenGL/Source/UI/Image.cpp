#include "stdafx.h"

#include "UI/Image.h"

#include <algorithm>


namespace OpenGL
{
  REGISTER_COMPONENT(Image);

  //------------------------------------------------------------------------------------------------
  Image::Image()
  {
  }

  //------------------------------------------------------------------------------------------------
  Image::~Image()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Image::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    ADD_AND_INITIALIZE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer);
  }

  //------------------------------------------------------------------------------------------------
  void Image::setSize(const glm::vec2& size)
  {
    const glm::vec2& imageDimensions = m_spriteRenderer.getTextureDimensions();
    ASSERT(imageDimensions.x > 0 && imageDimensions.y > 0);

    // We wish to maintain the aspect ratio of the object we are rendering
    float ratio = std::min(size.x / imageDimensions.x, size.y / imageDimensions.y);

    m_spriteRenderer.setScale(glm::vec2(ratio));
  }
}