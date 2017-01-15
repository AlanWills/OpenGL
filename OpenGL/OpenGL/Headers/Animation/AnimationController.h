#pragma once

#include "Objects/Component.h"
#include "Resources/Texture2D.h"
#include "Rendering/SpriteRenderer.h"


namespace OpenGL
{

class AnimationController : public Component
{
  DECLARE_COMPONENT(PoolAllocator, AnimationController, 10);

  public:
    void awake() override;
    void update(GLfloat secondsPerUpdate) override;

    /// \brief Add a new frame to the back of the frames list we will iterate over
    void addFrame(const Handle<Texture2D>& frame) { m_frames.push_back(frame); }
    void addFrame(const std::string& textureRelativePath);

    void setSecondsPerFrame(float secondsPerFrame) { m_secondsPerFrame = secondsPerFrame; }

  public:
    typedef Component Inherited;

    std::vector<Handle<Texture2D>> m_frames;
    size_t m_currentFrame;

    Handle<SpriteRenderer> m_spriteRenderer;

    float m_secondsPerFrame;
    float m_currentSecondsPerFrame;
};

}