#pragma once

#include "Objects/Component.h"
#include "Resources/Texture2D.h"
#include "Rendering/SpriteRenderer.h"


namespace OpenGL
{

class Animation : public Component
{
  DECLARE_COMPONENT(PoolAllocator, Animation, 10);

  public:
    void awake() override;
    void update(GLfloat secondsPerUpdate) override;

    /// \brief Add a new frame to the back of the frames list we will iterate over
    void addFrame(const Handle<Texture2D>& frame) { m_frames.push_back(frame); }
    void addFrame(const std::string& textureRelativePath);

    void setSecondsPerFrame(float secondsPerFrame) { m_secondsPerFrame = secondsPerFrame; }
    void setLoop(bool shouldLoop) { m_loop = shouldLoop; }

    /// \brief Will continue the animation at the current frame it was on
    /// With the current time left until the next frame
    /// If we resume a non-looping animation that reached it's end, nothing will happen
    void resume();

    /// \brief Will stop the animation at the current frame it was on
    /// With the current time left until the next frame
    /// If we pause a non-looping animation that reached it's end, nothing will happen
    void pause() { m_playing = false; }

    /// \brief Will set the animation to the first frame and reset the current timer
    /// Whether the animation is playing or not will not be affected
    void restart();

  public:
    typedef Component Inherited;

    std::vector<Handle<Texture2D>> m_frames;
    size_t m_currentFrame;

    Handle<SpriteRenderer> m_spriteRenderer;

    float m_secondsPerFrame;
    float m_currentSecondsPerFrame;

    bool m_loop;
    bool m_playing;
};

}