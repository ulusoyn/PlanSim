#pragma once

#include "InputHandler.h"
#include "KeyBindings.h"
#include "GameTypes.h"
#include "GameServices.h"
#include "ActionPlaceBody.h"
#include <vector>
#include <unordered_map>
#include <memory>

class InputManager
{
private:
    GameServices& services;
    GameState m_gameState;
    std::vector<InputHandler> m_handlers;
    std::map<std::tuple<GameState, int>, ActionType> m_bindings = KeyBindings::GetDefaultBindings();
    std::map<std::tuple<GameState, int>, std::unique_ptr<IAction>> m_actions;

    
public:
    InputManager(GameServices& s): services(s){}

    void InitializeActions();

    void TriggerActions();

    void SetInputHandlers();
    
    void Update();


};