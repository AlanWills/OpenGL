#pragma once

#include "Objects/Script.h"


namespace SpaceGame
{
  namespace SpaceGameUI
  {
    class ComputerInteractionUI : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(ComputerInteractionUI)

      protected:
        void onSetGameObject(const Handle<GameObject>& gameObject) override;
        void onHandleInput() override;
        void onUpdate(GLfloat elapsedGameTime) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        Handle<GameObject> m_icon;
    };
  }
}