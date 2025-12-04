#pragma once

#include "raylib.h"
#include "Game.h"
#include "SolarSystem.h"

struct GameServices{
    Game& game;
    Camera3D& camera;
    SolarSystem& solarSystem;

    // Simple state interface
    GameState GetState() const { return game.GetGameState(); }
    void SetState(GameState s)   { game.ChangeGameState(s); }
};