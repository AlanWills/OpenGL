#include "stdafx.h"

#include "UI/Button.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  const float Button::s_maxTime = 0.1f;

  //------------------------------------------------------------------------------------------------
  Button::Button() :
    m_clickTimer(0),
    m_state(kIdle),
    m_defaultTexture(nullptr),
    m_highlightedTexture(nullptr),
    m_clickedTexture(nullptr),
    m_highlightedAudio(nullptr),
    m_clickedAudio(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  Button::~Button()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Button::initialize(const Handle<Component>& allocHandle)
  {
    Inherited::initialize(allocHandle);

    ADD_AND_INITIALIZE_CLASS_COMPONENT(RectangleCollider, m_collider);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(AudioSource, m_audio);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(Label, m_label);

    // Anchor the label to this button and move it in front of it slightly
    m_label.getTransform()->setParent(getTransform());

    ResourceManager* resourceManager = GameManager::getResourceManager();
    m_defaultTexture = resourceManager->loadTexture("ButtonDefault.png");
    ASSERT(m_defaultTexture.get());

    m_highlightedTexture = resourceManager->loadTexture("ButtonHighlighted.png");
    ASSERT(m_highlightedTexture.get());

    m_clickedTexture = resourceManager->loadTexture("ButtonPressed.png");
    ASSERT(m_clickedTexture.get());

    m_spriteRenderer.setTexture(m_defaultTexture);

    m_collider.setDimensions(m_spriteRenderer.getDimensions());

    m_mouseInteraction.addOnEnterEvent(std::bind(&Button::onEnter, this, std::placeholders::_1));
    m_mouseInteraction.addOnLeaveEvent(std::bind(&Button::onLeave, this, std::placeholders::_1));
    m_mouseInteraction.addOnLeftClickEvent(std::bind(&Button::onLeftClick, this, std::placeholders::_1));

    m_highlightedAudio = resourceManager->loadAudio("ButtonHover.wav");
    ASSERT(m_highlightedAudio.get());

    m_clickedAudio = resourceManager->loadAudio("ButtonPressed.wav");
    ASSERT(m_clickedAudio.get());
  }

  //------------------------------------------------------------------------------------------------
  void Button::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_clickTimer += secondsPerUpdate;
    
    if (m_state == kClicked && m_clickTimer > s_maxTime)
    {
      if (m_collider.intersects(GameManager::getInputManager()->getMouse()->getMousePosition()))
      {
        m_spriteRenderer.setTexture(m_highlightedTexture);
        m_state = kHighlighted;
      }
      else
      {
        m_spriteRenderer.setTexture(m_defaultTexture);
        m_state = kIdle;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Button::onEnter(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture(m_highlightedTexture);
    m_audio.setAudio(m_highlightedAudio);
    m_audio.play();

    m_state = kHighlighted;
  }

  //------------------------------------------------------------------------------------------------
  void Button::onLeave(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture(m_defaultTexture);
  }

  //------------------------------------------------------------------------------------------------
  void Button::onLeftClick(Handle<GameObject> sender)
  {
    if (m_state != kClicked)
    {
      m_spriteRenderer.setTexture(m_clickedTexture);
      m_audio.setAudio(m_clickedAudio);
      m_audio.play();

      m_state = kClicked;
      m_clickTimer = 0;
    }
  }
}