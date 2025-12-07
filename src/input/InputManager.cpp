#include "core/GameServices.h"
#include "core/GameTypes.h"
#include "input/IAction.h"
#include "input/InputManager.h"
#include "input/InputHandler.h"
#include "input/KeyBindings.h"
#include "input/InputContext.h"
#include "ui/OutputContext.h"

#include "input/actions/ActionPlaceBody.h"
#include "input/actions/ActionSelectAndDragBody.h"
#include "input/actions/ActionChangeToggleMode.h"

#include <iostream>
#include <functional>
#include <memory>

InputManager::InputManager(GameServices& s, InputContext& ictx, OutputContext& octx, KeyBindings k) 
:   services(s), 
    m_bindings(k.GetDefaultBindings()), 
    ictx(ictx), 
    octx(octx)
{
    m_gameState = s.GetState();
    InitializeHandlers();
    InitializeActions();
}

std::unique_ptr<IAction> InputManager::CreateAction(ActionType type) {
    switch (type) {
    case ActionType::PlaceObject:
        return std::make_unique<ActionPlaceBody>();
    case ActionType::SelectAndDrag:
        return std::make_unique<ActionSelectandDragBody>();
    case ActionType::ToggleMode:
        return std::make_unique<ActionChangeToggleMode>();
    default:
        return nullptr;
    }
}

void InputManager::Update()
{
    m_gameState = services.GetState();
    
    // Update input context
    ictx.mousePos = GetMousePosition();
    
    // Update handlers
    for (auto& [inputKey, handler] : m_handlers)
    {
        handler.Update();
    }
    
    for (auto& [key, actionType] : m_bindings)
    {
        auto [bindingState, input] = key;
        
        if (bindingState != m_gameState) 
        {
            continue;
        }
        
        auto it = m_actions.find(key);
        if (it == m_actions.end()) 
        {
            continue;
        }
        
        IAction* action = it->second.get();
        
        auto handlerIt = m_handlers.find(input);
        if (handlerIt == m_handlers.end()) 
        {
            continue;
        }
        
        InputHandler* handler = &(handlerIt->second);
        
        ActionMode mode = ActionMode::None;
        
        if (handler->IsJustPressed())
        {
            mode = ActionMode::Trigger;
        }
        else if (handler->IsHeld())
        {
            mode = ActionMode::Hold;
        }
        else if (handler->IsReleased())
        {
            mode = ActionMode::Release;
        }
        
        if (mode != ActionMode::None)
        {
            action->Execute(mode, ictx, services, octx);
        }
    }
}

void InputManager::InitializeHandlers() {
    // Create a handler for each unique input key in bindings
    for (const auto& [key, actionType] : m_bindings) {
        auto [gameState, inputKey] = key;
        
        if (m_handlers.find(inputKey) == m_handlers.end()) {
            m_handlers.emplace(inputKey, InputHandler(inputKey));
        }
    }
}

void InputManager::InitializeActions(){
    for (const auto& [key, actionType] : m_bindings) {
        auto [gState, inputKey] = key;

        auto action = CreateAction(actionType);

        if (action)
        {
            m_actions.try_emplace(key, std::move(action));
        }
        if (m_handlers.find(inputKey) == m_handlers.end()) {
            m_handlers.emplace(inputKey, InputHandler(inputKey));
        }
    }
}