#pragma once

#include "raylib.h"

class Game;
class SolarSystem;

struct GameServices{
    Game* game;
    Camera3D* camera;
    SolarSystem* solarSystem;

    // Simple state interface
    GameState GetState() const;
    void SetState(GameState s);
};