#pragma once
#include "GameTypes.h"
#include "raylib.h"

struct InputContext{
    Vector2 mousePos;
    Camera3D camera;
    float deltaTime;
    GameState gameState;
};
