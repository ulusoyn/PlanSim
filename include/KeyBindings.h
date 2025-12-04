#pragma once
#include "GameTypes.h"
#include "raylib.h"
#include <map>
#include <tuple>

class KeyBindings {
public:
    static std::map<std::tuple<GameMode, int, ButtonCommand>, ActionType> GetDefaultBindings() {
        return {
            // Toggle mode
            {{GameMode::CameraControl, KEY_F, ButtonCommand::Trigger}, ActionType::ToggleMode},
            {{GameMode::EditingMode, KEY_F, ButtonCommand::Trigger}, ActionType::ToggleMode},
            
            // Camera
            {{GameMode::CameraControl, KEY_Z, ButtonCommand::Trigger}, ActionType::ResetCamera},
            {{GameMode::CameraControl, KEY_P, ButtonCommand::Trigger}, ActionType::SwitchProjection},
            
            // Placing
            {{GameMode::EditingMode, KEY_C, ButtonCommand::Trigger}, ActionType::StartPlacing},
            {{GameMode::EditingMode, KEY_C, ButtonCommand::Hold}, ActionType::UpdatePlacing},
            {{GameMode::EditingMode, KEY_C, ButtonCommand::Release}, ActionType::FinishPlacing},
        };
    }
};