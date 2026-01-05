# Input System & Game Architecture -- Planned Updates

This document describes the planned refactoring and extension of the
input, action, and game-state architecture. The goal is to achieve a
clear layer-based design that scales with new features (tools, UI,
modes) without exponential complexity.

## Current Situation (Summary)

-   Input is handled via InputHandler and InputManager
-   Actions are represented by IAction and ActionType
-   GameState currently drives most input branching
-   Tools exist conceptually but are not yet integrated
-   Key bindings are hard-coded in C++

This works, but coupling between GameState, input, and actions is
starting to grow.

## Target Architecture (High-Level)

### Core Principles

1.  Input produces *intent* (ActionType), not behavior
2.  GameState controls *which input layers are active*
3.  InputLayer controls *which bindings are valid*
4.  Actions modify Game / Editor state via GameServices
5.  Tools belong to editor logic, not input logic

### Key Concepts

-   GameState: High-level mode (Gameplay, Editing, Options)
-   InputLayer: Input routing layer (Global, Gameplay, Editor, UI)
-   ActionType: Semantic intent from user input
-   ActionMode: Temporal state of input (Trigger, Hold, Release)
-   Tools: Active editor tool (Place, Drag, Delete)

## Planned Changes

### 1. Introduce InputLayer formally

-   Add InputLayer enum to core types
-   Decouple bindings from GameState
-   Route input via active layers instead of states

### 2. Refactor Key Bindings

-   Bind (InputLayer, PhysicalInput) → ActionType
-   Move GameState logic out of key binding lookup
-   Keep bindings declarative and minimal

### 3. Centralize Layer Activation Logic

-   Game owns mapping: GameState → active InputLayers
-   InputManager queries active layers each frame
-   UI and Editor can push/pop layers if needed later

### 4. Clarify Action vs Tool Responsibilities

-   Actions set or query Tools
-   Tools drive editor behavior
-   InputManager never references Tools

### 5. Prepare for Data-Driven Bindings (Later)

-   Keep current C++ bindings for now
-   Design binding format for future JSON/text loading
-   Enable user rebinds without architectural changes

## Non-Goals (For Now)

-   No scripting
-   No full command stack / undo system
-   No user-facing keybind UI yet

## Design Rule (Important)

Input → ActionType → Action → State/Tool → Behavior

Never invert this flow.
