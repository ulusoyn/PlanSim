#pragma once

#include "core/GameServices.h"
#include "core/GameTypes.h"
#include "input/IAction.h"
#include "input/InputManager.h"
#include "input/InputContext.h"
#include "input/KeyBindings.h"
#include "physics/SolarSystem.h"
#include "rendering/CameraHandler.h"
#include "ui/GUIService.h"
#include "ui/OutputContext.h"


#include <unordered_map>

class Game
{
private:

    CameraHandler   m_cameraHandler;
    GameState       m_currentGameState;
    GameServices    m_services;
    GUIService      m_guiService;
    InputContext    m_inputContext;
    InputManager    m_inputManager;
    KeyBindings     m_keyBindings;
    OutputContext   m_outputContext;
    SolarSystem     m_solarSystem;
    Tools           m_currentTool;

    
    bool m_isCursorVisible;
    bool m_isRunning;
    bool m_showDemoWindow;

    const int screenWidth;
    const int screenHeight;

    void ToggleMode();
    void PlaceBodyMode();
    void DragBodyMode();
    void DeleteBodyMode();
    
public:
    Game(const int screenWidth, const int screenHeight);
    ~Game();
    void InitializeKeyBindings();
    void Update();
    void Render();
    void Run();
    
    void ChangeGameState(GameState newMode);
    void ChangeCurrentTool(Tools t) { m_currentTool = t; }
    void ChangeCursorVisibility(bool isVisible) { m_isCursorVisible = isVisible; }

    Tools GetCurrentTool() const { return m_currentTool; }
    GameState GetGameState(){ return m_currentGameState;}

    bool IsRunning() const { return m_isRunning; }
};