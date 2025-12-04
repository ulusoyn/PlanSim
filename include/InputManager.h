#pragma once
#include "InputHandler.h"
#include "Action.h"
#include <vector>
#include <unordered_map>

class InputManager
{
private:
    std::unordered_map<int, InputHandler> m_inputHandlersFlat; // keycode to InputHandler mapping
    std::unordered_map<GameMode,std::unordered_map<int, Action>> m_inputHandlers; // keycode to InputHandler mapping
    
public:
    InputManager();

    void SetInputHandlers();
    
    void Update();


};