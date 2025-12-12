#pragma once
#include "core/GameTypes.h"
#include "raylib.h"
#include <map>
#include <tuple>

class KeyBindings {
public:
    KeyBindings(){}
    static std::map<int, ActionType> GetGlobalBindings() {
        return {
            { KEY_ESCAPE, ActionType::ToggleOptionMenu },
            { KEY_F,      ActionType::ToggleCursor},
        };
    }

    
    static std::map<std::tuple<GameState, int>, ActionType> GetDefaultBindings() {
        return {
            // Toggle mode
            {{GameState::EditingMode, KEY_C}, ActionType::CreationMode},
            
            // Camera
            // {{GameState::CameraControl, KEY_Z}, ActionType::ResetCamera},
            // {{GameState::CameraControl, KEY_P}, ActionType::SwitchProjection},
            
            // Placing
            {{GameState::EditingMode, MOUSE_BUTTON_LEFT}, ActionType::PlaceObject},

            // Dragging
            {{GameState::EditingMode, KEY_V}, ActionType::SelectAndDrag},

            // Note: Dragging and placing can be combined. Could be identified 
            // by checking if the mouse ray hitting a planet or not. 
        };
    }
};