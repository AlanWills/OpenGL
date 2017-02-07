#pragma once

#include "Resources/ResourceManager.h"
#include "Screens/ScreenManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Audio/AudioManager.h"
#include "Time/Clock.h"

#include <memory>

class PhysicsManager;

using namespace CelesteEngine;


namespace OpenGL
{

/// Grouper class for all of the game managers
/// Also contains general meta data about the game and window
class GameManager
{
  public:
    /// \brief Initialise all of the managers associated with the game
    static void init();

    /// \brief Begin our game loop
    static void run();

    /// \brief Exits the application
    static void exit();

    /// \brief GameManager takes responsibility for managing the resource manager
    static void setResourceManager(ResourceManager* resourceManager);
    static ResourceManager* getResourceManager();

    /// \brief GameManager takes responsibility for managing the screen manager
    static void setScreenManager(ScreenManager* screenManager);
    static ScreenManager* getScreenManager();

    /// \brief GameManager takes responsibility for managing the input manager
    static void setInputManager(InputManager* inputManager);
    static InputManager* getInputManager();

    /// \brief GameManager takes responsibility for managing the physics manager
    static void setPhysicsManager(PhysicsManager* physicsManager);
    static PhysicsManager* getPhysicsManager();

    /// \brief GameManager takes responsibility for managing the audio manager
    static void setAudioManager(AudioManager* audioManager);
    static AudioManager* getAudioManager();

    /// \brief GameManager takes responsibility for manager the clock
    static void setGameClock(Clock* clock);
    static Clock* getGameClock();

  private:
    GameManager();
    ~GameManager();

    static void awake();
    static void handleInput(GLfloat elapsedGameTime);
    static void update(GLfloat gameSecondsPerUpdate);
    static void render(GLfloat lag);

    /// \brief The manager responsible for handling game resources
    static std::unique_ptr<ResourceManager> m_resourceManager;

    /// \brief The manager responsible for handling screens
    static std::unique_ptr<ScreenManager> m_screenManager;

    /// \brief The manager responsible for handling and processing human input
    static std::unique_ptr<InputManager> m_inputManager;

    /// \brief The manager responsible for handling and simulating physics
    static std::unique_ptr<PhysicsManager> m_physicsManager;
    
    /// \brief The manager responsible for playing and maintaining audio
    static std::unique_ptr<AudioManager> m_audioManager;

    /// \brief The game clock responsible for managing game time
    /// This clock can have it's speed altered to change the speed of the game, but not the game loop itself
    static std::unique_ptr<Clock> m_gameClock;
};

}