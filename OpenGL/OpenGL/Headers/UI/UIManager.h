#pragma once

#include "Objects/Component.h"
#include "Resources/Shader.h"
#include "Memory/ComponentAllocator.h"
#include "UI/Button.h"
#include "UI/Image.h"


namespace OpenGL
{

class UIManager : public Component
{
  #define BUTTON_POOL_SIZE 10
  #define IMAGE_POOL_SIZE 10

  public:
    UIManager();
    virtual ~UIManager();

    void initialize(Handle<Component> allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;
    void die() override;

  private:
    typedef Component Inherited;

    static StringId s_spriteShaderId;
    Handle<Shader> m_spriteShader;

    static StringId s_textShaderId;
    Handle<Shader> m_textShader;
    
    DECLARE_CLASS_COMPONENT_ALLOCATOR(Button, BUTTON_POOL_SIZE, m_buttons)
    DECLARE_CLASS_COMPONENT_ALLOCATOR(Image, IMAGE_POOL_SIZE, m_images)
};

}