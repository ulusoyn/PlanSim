#pragma once

#include "SolarSystem.h"
#include "CameraHandler.h"
#include "InputManager.h"
#include "raylib.h"
#include "Simmode.h"



class Game
{
private:
    std::unique_ptr<SolarSystem> m_solarSystem;
    CameraHandler m_cameraHandler;
    InputHandler m_inputManager;
    Simmode m_currentMode;
    bool m_isRunning;

public:
    Game();
    void Update();
    void Draw();
    bool IsRunning() const { return m_isRunning; }
}