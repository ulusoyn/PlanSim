#pragma once

// This file defines various game-related enumerations used across the project.


enum class GameState {
    CameraControl,
    EditingMode,
};


enum class ActionMode {
    Trigger,   // JustPressed
    Hold,      // Held
    Release,   // Released
    JustReleased,
    None       // None
};

enum class ActionType {
    None,  // For "not found" cases
    
    // Mode switching
    ToggleMode,
    CreationMode,
    DragMode,
    FreeLookMode,
    OptionsMode,
    
    // Camera actions
    ResetCamera,
    SwitchProjection,
    
    // Editing actions
    PlaceObject,
    SelectAndDrag,
    DeleteBody,
    ApplyForce,
    
};