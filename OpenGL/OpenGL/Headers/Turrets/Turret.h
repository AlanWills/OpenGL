#pragma once

#include "Objects/GameObject.h"
#include "Objects/Script.h"


namespace SpaceGame
{

class Turret : public CelesteEngine::Script
{
  DECLARE_SCRIPT(Turret)

  public:
    static void create(const Handle<GameObject>& turret);

    void fire();

  protected:
    void onUpdate(GLfloat elapsedGameTime);
    void onDeath();

  private:
    typedef CelesteEngine::Script Inherited;

    float m_currentFireTimer;
};

}