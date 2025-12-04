#pragma once

#include "SolarSystem.h"
#include "CameraHandler.h"
#include "IAction.h"
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
    GameState m_currentGameState;

    std::unordered_map<ActionType, IAction> m_actions;

    bool m_isRunning;
    
    void InitializeActions();

    void ToggleMode();
    void PlaceBodyMode();
    void DragBodyMode();
    void DeleteBodyMode();
    
    public:
    Game();
    void ChangeGameState(GameState newMode);
    GameState GetGameState(){ return m_currentGameState;}
    void Update();
    void Draw();
    bool IsRunning() const { return m_isRunning; }

};