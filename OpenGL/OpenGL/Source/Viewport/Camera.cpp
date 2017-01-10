#include "stdafx.h"

#include "Viewport/Camera.h"
#include "Game/GameManager.h"
#include "Scripts/ScriptManager.h"
#include "Input/KeyboardMovementScript.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Camera::Camera() :
    m_aspectRatio(1),
    m_nearPlane(0.1f),
    m_farPlane(100)
  {
  }

  //------------------------------------------------------------------------------------------------
  Camera::~Camera()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Camera::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    getTransform()->setLocalMatrix(glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(), glm::vec3(0, 1, 0)));

    if (KeyboardMovementScript::canAllocate())
    {
      Handle<KeyboardMovementScript> keyboardMovementScript = addComponent<kUnmanaged>(KeyboardMovementScript::allocateAndInitialize());
      keyboardMovementScript->setMoveUpKey(GLFW_KEY_S);
      keyboardMovementScript->setMoveDownKey(GLFW_KEY_W);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Camera::pan(const glm::vec3& translation)
  {
    getTransform()->translate(translation);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getPerspectiveProjectionMatrix() const
  {
    return glm::perspective<float>(45.0f, m_aspectRatio, m_nearPlane, m_farPlane);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getOrthographicProjectionMatrix() const
  {
    return glm::ortho<float>(0, GameManager::getScreenManager()->getViewportWidth(), 0, GameManager::getScreenManager()->getViewportHeight());
  }

  //------------------------------------------------------------------------------------------------
  const glm::mat4& Camera::getViewMatrix() const
  {
    // Maybe expand this later, but for now it's going to be a top down camera
    return getTransform()->getLocalMatrix();
  }

  //------------------------------------------------------------------------------------------------
  Ray Camera::createRay(const glm::vec2& screenPosition) const
  {
    Ray ray;
    ray.m_origin = getTransform()->getLocalTranslation();

    float screenWidth = GameManager::getScreenManager()->getViewportWidth();
    float screenHeight = GameManager::getScreenManager()->getViewportHeight();

    float mouseX = screenPosition.x / (screenWidth  * 0.5f) - 1.0f;
    float mouseY = screenPosition.y / (screenHeight * 0.5f) - 1.0f;

    glm::mat4 invVP = glm::inverse(getPerspectiveProjectionMatrix() * getViewMatrix());
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    ray.m_direction = glm::normalize(glm::vec3(worldPos));

    return ray;
  }

  //------------------------------------------------------------------------------------------------
  void Camera::setAspectRatio(float aspectRatio)
  {
    if (!aspectRatio > 0)
    {
      ASSERT_FAIL();
      return;
    }

    m_aspectRatio = aspectRatio;
  }
}