#pragma once

// This file defines various game-related enumerations used across the project.

enum class GameMode {
    CameraControl,
    EditingMode,
    FreeTravelMode
};

enum class ButtonCommand {
    Trigger,   // JustPressed
    Hold,      // Held
    Release    // JustReleased
};

enum class ActionType {
    None,  // For "not found" cases
    
    // Mode switching
    ToggleMode,
    
    // Camera actions
    ResetCamera,
    SwitchProjection,
    
    // Editing actions
    StartPlacing,
    UpdatePlacing,
    FinishPlacing,
    
    StartDragging,
    UpdateDragging,
    FinishDragging,
    
    DeleteBody
    
    // Add more as needed
};