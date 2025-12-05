#pragma once

#include "core/GameTypes.h"
#include <map>
#include <vector>
#include <memory>

class GameServices;
class InputHandler;
class KeyBindings;
class GameServices;
class InputContext;
class OutputContext;

class InputManager
{
private:
    GameServices services;
    InputContext ictx;
    OutputContext octx;
    GameState m_gameState;
    std::map<int, InputHandler> m_handlers;
    // std::vector<InputHandler> m_handlers;
    std::map<std::tuple<GameState, int>, ActionType> m_bindings;
    std::map<std::tuple<GameState, int>, std::unique_ptr<IAction>> m_actions;

    
public:
    InputManager(GameServices& s, InputContext& ictx, OutputContext& octx, KeyBindings k);

    void InitializeActions();

    void TriggerActions();

    std::unique_ptr<IAction> CreateAction(ActionType type);
    
    void Update();


};