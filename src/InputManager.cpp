#include "InputManager.h"
#include "KeyBindings.h"

void InputManager::Update()
{
    for (auto& handler : m_handlers)
    {
        handler.Update();
    }
}

void InputManager::InitializeActions(){
    for (const auto& [key, actionType] : m_bindings) {
        switch (actionType)
        {
        case ActionType::PlaceObject:
            m_actions[key] = std::make_unique<ActionPlaceBody>();
            /* code */
            break;
        
        default:
            break;
        }
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