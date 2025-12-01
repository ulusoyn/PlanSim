#pragma once
#include "Constants.h"
#include <iostream>
#include <vector>
#include "raylib.h"
#include <memory>

class CelestialBody;

class SolarSystem
{
protected:
    std::vector<std::unique_ptr<CelestialBody>> m_bodies;
    float m_gravitationalConstant = SimPhysics::GRAVITATIONAL_CONSTANT; // Gravitational constant

public:
    SolarSystem();

    void Update(float deltaTime);
    void Draw();
    void AddBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity);
    void ApplyGravity();
    void ClearBodies();
};