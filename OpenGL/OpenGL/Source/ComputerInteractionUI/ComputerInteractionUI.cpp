#include "stdafx.h"

#include "UI/ComputerInteractionUI.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/InputManager.h"
#include "Screens/ScreenManager.h"
#include "Factories/GameScreenFactory.h"


using namespace CelesteEngine::Physics;
using namespace CelesteEngine::Input;

namespace SpaceGame
{
  namespace SpaceGameUI
  {
    REGISTER_SCRIPT(ComputerInteractionUI, 3);

    //------------------------------------------------------------------------------------------------
    ComputerInteractionUI::ComputerInteractionUI() :
      m_icon()
    {
    }

    //------------------------------------------------------------------------------------------------
    ComputerInteractionUI::~ComputerInteractionUI()
    {
    }

    //------------------------------------------------------------------------------------------------
    void ComputerInteractionUI::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_icon = gameObject->allocateGameObjectInSameLayer();
      m_icon->getTransform()->setTranslation(gameObject->getTransform()->getTranslation() + glm::vec3(0, 100, 0.01f));
      const Handle<SpriteRenderer>& iconRenderer = SpriteRenderer::create(m_icon, Path("Sprites", "UI", "UpDirectionIndicator.png"));
      m_icon->setShouldRender(false);
    }

    //------------------------------------------------------------------------------------------------
    void ComputerInteractionUI::onHandleInput()
    {
      Inherited::onHandleInput();

      if (m_icon->shouldRender() && getKeyboard().isKeyDown(GLFW_KEY_UP))
      {
        deactivateOwnerScreen(getGameObject());
        activateScreen("Terminal");
      }
    }

    //------------------------------------------------------------------------------------------------
    void ComputerInteractionUI::onUpdate(GLfloat elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);

      const Handle<GameObject>& player = getGameObject()->getOwnerScreen()->findGameObjectWithName("Player");
      m_icon->setShouldRender(player->findComponent<Collider>()->intersects(getGameObject()->findComponent<RectangleCollider>()->rectangle()));
    }

    //------------------------------------------------------------------------------------------------
    void ComputerInteractionUI::onDeath()
    {
      Inherited::onDeath();

      m_icon->die();
      m_icon.reset();
    }
  }
}