#ifndef SNAPSHOTS_HPP
#define SNAPSHOTS_HPP

#include "SolarSystem.h"
#include "raymath.h"

namespace PlanetSimulator {

struct GameSnapshot
{
    const SolarSystem& solarSystem;
};

struct InputSnapshot
{
    Vector2 mousePosition;
    Vector2 mouseDelta;
    float deltaTime;
};

}

#endif // SNAPSHOTS_HPP