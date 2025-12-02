#pragma once

#include "InputManager.h"
#include "InputBindings.h"


void InputManager::Update()
{
    for (auto& handler : m_inputHandlers)
    {
        handler.second.Update();
    }
}

void InputManager::SetInputHandlers()
{
    // Example keycodes, replace with actual keycodes as needed
    std::vector<int> keyCodes = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, MOUSE_LEFT_BUTTON };

    for (int keyCode : keyCodes)
    {
        m_inputHandlers.emplace(keyCode, InputHandler(keyCode));
    }
}