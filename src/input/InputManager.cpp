#include "core/GameServices.h"
#include "core/GameServices.h"
#include "input/InputManager.h"
#include "input/InputHandler.h"
#include "input/KeyBindings.h"
#include "input/InputContext.h"
#include "input/actions/ActionPlaceBody.h"
#include "input/actions/ActionSelectAndDragBody.h"
#include "ui/OutputContext.h"

#include <functional>

InputManager::InputManager(GameServices& s, InputContext& ictx, OutputContext& octx, KeyBindings k) : 
    services(s), m_bindings(k.GetDefaultBindings()), ictx(ictx), octx(octx)
{
    m_gameState = s.GetState();
    InitializeActions();
}

std::unique_ptr<IAction> InputManager::CreateAction(ActionType type) {
    switch (type) {
    case ActionType::PlaceObject:
        return std::make_unique<ActionPlaceBody>();
    case ActionType::SelectAndDrag:
        return std::make_unique<ActionSelectandDragBody>();
    // case ActionType::DeleteBody:
    //     return std::make_unique<ActionDeleteBody>();
    default:
        return nullptr;
    }
}

void InputManager::Update()
{
    m_gameState = services.GetState();
    for (auto& handler : m_handlers)
    {
        handler.second.Update();
    }

    for (auto& [key, ActionType] : m_bindings)
    {
        auto it = m_actions.find(key);
        if (it != m_actions.end())
        {
            IAction* action = it->second.get();
            int input = std::get<1>(key);
            InputHandler* handler = &(m_handlers[input]);
            ActionMode mode;
            if (handler->IsReleased())
            {
                mode = ActionMode::Release;
            }
            else if (handler->IsHeld())
            {
                mode = ActionMode::Hold;
            }
            if (handler->IsJustPressed())
            {
                mode = ActionMode::Trigger;
            }
            action->Execute(mode, ictx, services, octx);
        }
    }
}

void InputManager::InitializeActions(){
    for (const auto& [key, actionType] : m_bindings) {
        auto action = CreateAction(actionType);
        m_actions.try_emplace(key, std::move(action));

    }
}

void InputManager::TriggerActions(){

}



// void InputManager::SetInputHandlers()
// {
//     // Example keycodes, replace with actual keycodes as needed
//     std::vector<int> keyCodes = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, MOUSE_LEFT_BUTTON };

//     for (int keyCode : keyCodes)
//     {
//         m_inputHandlers.emplace(keyCode, InputHandler(keyCode));
//     }
// }