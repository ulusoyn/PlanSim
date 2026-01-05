#pragma once

// This file defines various game-related enumerations used across the project.

enum class InputLayer{
    Global,
    GamePlay,           // Understand what this layer is for
    Editor,             // Understand what this layer is for
    UI
};



// Game state controls which system mode is active
// In this game, camera control is free movement in the space
// where editing mode allows object manipulation and creation
// option mode is for menus and settings

// The default mode is CameraControl and game state can be changed with inputs
enum class GameState {
    CameraControl,
    EditingMode,
    OptionMode,
};


// Tools define what the editor is currently using

// The functionality of keys can change based on the current tool selected
// Same key can be used for different actions depending on the tool
enum class Tools {
    None,
    PlaceBody,
    DragBody,
    DeleteBody,
};


// Action modes define the type of input action being performed
// Action modes cannot be changed. There are total of 5 modes.
enum class ActionMode {
    Trigger,   // JustPressed
    Hold,      // Held
    Release,   // Released
    JustReleased,
    None       // None
};

// Action types define the various actions that can be performed in the game
enum class ActionType {
    None,  // For "not found" cases

    // Menu
    ToggleOptionMenu,
    
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