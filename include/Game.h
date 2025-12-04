#pragma once

#include "SolarSystem.h"
#include "CameraHandler.h"
#include "InputManager.h"
#include "GameTypes.h"
#include "Simmode.h"



class Game
{
private:
    std::unique_ptr<SolarSystem> m_solarSystem;
    CameraHandler m_cameraHandler;
    InputHandler m_inputManager;
    Simmode m_currentMode;
    GameMode m_CurrentGameMode;

    std::unordered_map<ActionType, Action> m_actions;

    bool m_isRunning;
    
    void InitializeActions();

    void ToggleMode();
    void ChangeGameMode(GameMode newMode);
    void PlaceBodyMode();
    void DragBodyMode();
    void DeleteBodyMode();

public:
    Game();
    void Update();
    void Draw();
    bool IsRunning() const { return m_isRunning; }

}