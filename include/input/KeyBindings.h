#pragma once
#include "core/GameTypes.h"
#include "raylib.h"
#include <map>
#include <tuple>

class KeyBindings {
public:
    static std::map<std::tuple<GameState, int>, ActionType> GetDefaultBindings() {
        return {
            // Toggle mode
            {{GameState::CameraControl, KEY_F}, ActionType::ToggleMode},
            {{GameState::EditingMode, KEY_F}, ActionType::ToggleMode},
            
            // Camera
            {{GameState::CameraControl, KEY_Z}, ActionType::ResetCamera},
            {{GameState::CameraControl, KEY_P}, ActionType::SwitchProjection},
            
            // Placing
            {{GameState::EditingMode, KEY_C}, ActionType::PlaceObject},

            // Dragging
            {{GameState::EditingMode, KEY_V}, ActionType::DragObject},

            // Note: Dragging and placing can be combined. Could be identified 
            // by checking if the mouse ray hitting a planet or not. 
        };
    }
};