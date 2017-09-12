#include "stdafx.h"

#include "Controllers/PlayerController.h"
#include "Objects/GameObject.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Screens/ScreenUtils.h"
#include "Screens/Screen.h"


using namespace CelesteEngine::Rendering;
using namespace CelesteEngine::Input;

namespace SpaceGame
{
  REGISTER_SCRIPT(PlayerController, 1);

  //------------------------------------------------------------------------------------------------
  PlayerController::PlayerController() :
    m_playerRenderer(),
    m_controller(),
    m_minPosition(0),
    m_maxPosition(0),
    m_nextLevelPosition(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  PlayerController::~PlayerController()
  {
  }

  //------------------------------------------------------------------------------------------------
  void PlayerController::onSetGameObject(const Handle<GameObject>& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_playerRenderer = gameObject->findComponent<SpriteRenderer>();
    m_controller = gameObject->findComponent<KeyboardRigidBody2DController>();
  }

  //------------------------------------------------------------------------------------------------
  void PlayerController::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    const glm::vec3& translation = getTransform()->getTranslation();
    if (translation.x <= m_minPosition)
    {
      getTransform()->setTranslation(m_minPosition, translation.y, translation.z);
      m_controller->setDecreaseXLinearVelocityKey(-1);
    }
    else
    {
      m_controller->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    }

    if (translation.x >= m_maxPosition)
    {
      getTransform()->setTranslation(m_maxPosition, translation.y, translation.z);
      m_controller->setIncreaseXLinearVelocityKey(-1);
    }
    else
    {
      m_controller->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    }

    if (translation.x >= m_nextLevelPosition)
    {
      getGameObject()->getOwnerScreen()->die();
    }
  }
}