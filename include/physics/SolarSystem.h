#pragma once
#include "core/Constants.h"

#include "raylib.h"

#include <iostream>
#include <vector>
#include <memory>

class CelestialBody;

class SolarSystem
{
protected:
    std::vector<std::shared_ptr<CelestialBody>> m_bodies;
    float m_gravitationalConstant = SimPhysics::GRAVITATIONAL_CONSTANT; // Gravitational constant

public:
    SolarSystem();

    int GetBodyCount() {return static_cast<int>(m_bodies.size());}
    void Update(float deltaTime);
    void Draw();
    std::vector<std::shared_ptr<CelestialBody>>& GetBodies() { return m_bodies; }
    void AddBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity);
    void ApplyGravity();
    void ClearBodies();
};