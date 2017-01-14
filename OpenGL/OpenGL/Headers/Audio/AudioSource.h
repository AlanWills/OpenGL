#pragma once

#include "Objects/Component.h"
#include "Resources/Audio.h"


namespace OpenGL
{

class AudioSource : public Component
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, AudioSource, 10, AudioManager);

  public:
    void initialize(Handle<Component> allocHandle) override;
    void die() override;

    void setAudio(const std::string& wavFileRelativePath);
    void setAudio(const Handle<Audio>& audio);

    void play() const;

  private:
    typedef Component Inherited;

    Handle<Audio> m_audio;

    ALuint m_source;
};

}