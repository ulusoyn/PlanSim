# TODO -- Input & Architecture Refactor

## High Priority (Next Steps)

-   [ ] Add InputLayer enum to core types
-   [ ] Define active InputLayers per GameState in Game class
-   [ ] Refactor InputManager to query active layers instead of
    GameState
-   [ ] Update KeyBindings to use InputLayer instead of GameState
-   [ ] Remove GameState branching from input lookup

## Action System Cleanup

-   [ ] Review ActionType list and remove state-like entries
-   [ ] Ensure each ActionType represents semantic intent
-   [ ] Verify IAction implementations do not access raw input
-   [ ] Route all state/tool changes through GameServices

## Editor / Tool Integration

-   [ ] Decide single source of truth for active Tool
-   [ ] Implement Tool switching actions (Creation, Drag, Delete)
-   [ ] Ensure editor behavior depends on Tool, not ActionType

## Input Robustness

-   [ ] Support simultaneous active layers (Global + Editor, etc.)
-   [ ] Ensure ESC works from any layer via Global bindings
-   [ ] Validate ActionMode dispatch consistency (Trigger/Hold/Release)

## Code Organization

-   [ ] Keep GameTypes.h clean and concept-focused
-   [ ] Consider splitting types when file grows
-   [ ] Audit includes and replace with forward declarations where
    possible

## Later / Optional

-   [ ] Externalize key bindings to JSON or text
-   [ ] Add user-rebind support
-   [ ] Add debug overlay for active layers and actions
-   [ ] Add input recording/replay for debugging
