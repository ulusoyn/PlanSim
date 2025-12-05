#include "core/Game.h"
#include "core/GameServices.h"
#include "input/InputManager.h"
#include "input/InputContext.h"
#include "physics/SolarSystem.h"
#include "ui/OutputContext.h"

#include "pch.h"


Game::Game()
    : m_cameraHandler(
          Vector3{10.0f, 10.0f, 10.0f}, // position
          Vector3{0.0f, 0.0f, 0.0f},    // target
          Vector3{0.0f, 1.0f, 0.0f},    // up
          60.0f,                        // fovy
          CAMERA_PERSPECTIVE            // projection mode
      ),
      m_isCursorVisible(false),
      m_isRunning(true),
      m_solarSystem(SolarSystem()),
      m_services(GameServices{this, &m_cameraHandler.GetCamera(), &m_solarSystem}),
      m_inputManager(InputManager(m_services))
{
    m_inputContext = InputContext();
    m_outputContext = OutputContext();
    m_currentGameState = GameState::FreeTravelMode;
}

void Game::ChangeGameState(GameState newMode)
{
    m_currentGameState = newMode;
}

void Game::Update()
{
    m_inputManager.Update();
    m_solarSystem.Update(GetFrameTime());
    m_solarSystem.ApplyGravity();
    m_cameraHandler.CameraUpdate();

    if (!m_isCursorVisible)
    {
        DisableCursor();
    }
    else
    {
        EnableCursor();
    }
}
