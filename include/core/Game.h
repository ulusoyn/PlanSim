#pragma once

#include "rendering/CameraHandler.h"
#include "input/IAction.h"
#include "core/GameTypes.h"
#include <unordered_map>

class SolarSystem;
class InputManager;
class GameServices;
class InputContext;
class OutputContext;

class Game
{
private:

    CameraHandler   m_cameraHandler;
    GameState       m_currentGameState;
    GameServices    m_services;
    InputContext    m_inputContext;
    InputManager    m_inputManager;
    OutputContext   m_outputContext;
    SolarSystem     m_solarSystem;

    
    bool m_isCursorVisible;
    bool m_isRunning;

    void ToggleMode();
    void PlaceBodyMode();
    void DragBodyMode();
    void DeleteBodyMode();
    
public:
    Game();
    void Update();
    void Draw();
    void ChangeGameState(GameState newMode);
    void ChangeCursorVisibility(bool isVisible) { m_isCursorVisible = isVisible; }

    bool IsRunning() const { return m_isRunning; }

    GameState GetGameState(){ return m_currentGameState;}
};