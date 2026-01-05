#pragma once

#include "raylib.h"


class Game;
enum class GameState;
class SolarSystem;

struct GameServices{
    Game* game;
    Camera3D* camera;
    SolarSystem* solarSystem;

    // Simple state interface
    GameState GetState() const;
    Tools GetCurrentTool() const;
    void SetTool(Tools t);
    void SetState(GameState s);
    void SetCursor(bool isVisible);
};