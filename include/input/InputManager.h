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
// Forward Declarations


class InputManager
{
private:
    GameServices& services;
    InputContext& ictx;
    OutputContext& octx;
    GameState m_gameState; // Maybe change is needed for active layers

    std::map<int, InputHandler> m_handlers;

    std::map<std::tuple<GameState, int>, ActionType> m_bindings;
    std::map<ActionType, std::unique_ptr<IAction>> m_actionPrototypes; // Prototypes for each action type

    std::map<int, ActionType> m_globalBindings;
    std::map<int, std::unique_ptr<IAction>> m_gamePlayBindings;
    std::map<int, std::unique_ptr<IAction>> m_modalBindings;;

    
public:
    InputManager(GameServices& s, InputContext& ictx, OutputContext& octx, KeyBindings k);

    
    std::unique_ptr<IAction> CreateAction(ActionType type);
    
    
    void InitializeActions();
    void InitializeHandlers();
    
    void Update();
};