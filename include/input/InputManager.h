#pragma once

#include "core/GameTypes.h"
#include "input/InputHandler.h"
#include <map>
#include <vector>
#include <memory>

class KeyBindings;
class IAction;
struct GameServices;
struct InputContext;
struct OutputContext;

class InputManager
{
private:
    GameServices& services;
    InputContext& ictx;
    OutputContext& octx;
    GameState m_gameState;
    std::map<int, InputHandler> m_handlers;
    // std::vector<InputHandler> m_handlers;
    std::map<std::tuple<GameState, int>, ActionType> m_bindings;
    std::map<std::tuple<GameState, int>, std::unique_ptr<IAction>> m_actions;

    
public:
    InputManager(GameServices& s, InputContext& ictx, OutputContext& octx, KeyBindings k);

    void InitializeActions();
    void InitializeHandlers();
    
    std::unique_ptr<IAction> CreateAction(ActionType type);
    
    void Update();


};