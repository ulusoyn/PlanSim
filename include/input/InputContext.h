#pragma once

#include "core/GameTypes.h"
#include "raylib.h"

struct InputContext{
    Vector2 mousePos;
    Vector2 mouseDelta;
    Camera3D camera;
    float deltaTime;
    GameState gameState;
};
