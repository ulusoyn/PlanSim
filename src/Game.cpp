#include "Game.h"

void Game::InitializeActions()
{
    // Example action initialization
    m_actions[ActionType::ToggleMode] = Action{
        "Toggle Mode",
        [this]() { this->ToggleMode(); },
        true
    };

    m_actions[ActionType::StartPlacing] = Action{
        "Place Body",
        [this]() { this->PlaceBodyMode(); },
        true
    };

    m_actions[ActionType::UpdatePlacing] = Action{
        "Update Placing Body",
        [this]() { /* Implementation for updating placing a body */ },
        true
    };

    m_actions[ActionType::FinishPlacing] = Action{
        "Finish Placing Body",
        [this]() { /* Implementation for finishing placing a body */ },
        true
    };
    
    m_actions[ActionType::StartDragging] = Action{
        "Start Dragging Body",
        [this]() { /* Implementation for starting to drag a body */ },
        true
    };

    m_actions[ActionType::StartDragging] = Action{
        "Drag Body",
        [this]() { this->DragBodyMode(); },
        true
    };

    m_actions[ActionType::UpdateDragging] = Action{
        "Drag Body",
        [this]() { this->DragBodyMode(); },
        true
    };

    m_actions[ActionType::FinishDragging] = Action{
        "Drag Body",
        [this]() { this->DragBodyMode(); },
        true
    };

    m_actions[ActionType::DeleteBody] = Action{
        "Delete Body",
        [this]() { this->DeleteBodyMode(); },
        true
    };
}