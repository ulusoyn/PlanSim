#pragma once

// This file defines various game-related enumerations used across the project.

enum class GameState {
    CameraControl,
    EditingMode,
    FreeTravelMode
};


enum class ActionMode {
    Trigger,   // JustPressed
    Hold,      // Held
    Release    // JustReleased
};

enum class ActionType {
    None,  // For "not found" cases
    
    // Mode switching
    ToggleMode,
    FreeLookMode,
    OptionsMode,
    
    // Camera actions
    ResetCamera,
    SwitchProjection,
    
    // Editing actions
    PlaceObject,
    DragObject,
    DeleteBody,
    ApplyForce,
    
};