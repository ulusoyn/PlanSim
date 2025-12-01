#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class CelestialBody {
protected:
    std::string m_name;
    
    Color m_color;

    float m_mass;
    float m_radius;
    float m_limit = 100.0f; // Boundary limit for simple collision
    
    Vector3 m_position;
    Vector3 m_velocity;
    Vector3 m_acceleration;
    Vector3 m_forceAccumulator;
    std::vector<Vector3> m_trail;
    
public:
    // Notice how clear the constructor becomes:
    // "m_mass" is the class variable. "mass" is the input argument.
    CelestialBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity);
    CelestialBody(float radius, Vector3 position);

    virtual ~CelestialBody() = default;

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void ApplyForce(Vector3 force);

    // Getters
    Vector3 GetPosition() const { return m_position; }
    float GetMass() const { return m_mass; }
};