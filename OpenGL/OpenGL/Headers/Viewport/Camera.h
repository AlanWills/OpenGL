#pragma once

#include "GLHeaders.h"


namespace OpenGL
{

class Camera
{
  public:
    Camera();

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
};

}