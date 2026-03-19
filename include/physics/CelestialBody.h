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
    
    Model  m_model;
    bool   m_hasTexture = false;

public:
    // Notice how clear the constructor becomes:
    // "m_mass" is the class variable. "mass" is the input argument.
    CelestialBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity);
    CelestialBody(float radius, Vector3 position);

    virtual ~CelestialBody();

    void LoadBodyTexture(const char* texturePath);
    void Initialize(); 

    virtual void ChangeColor(Color newColor) { m_color = newColor; }
    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void DrawWires(Color color);
    virtual void ApplyForce(Vector3 force);

    // Getters
    float GetMass() const { return m_mass; }
    float GetRadius() const { return m_radius; }
    Vector3 GetPosition() const { return m_position; }
    Vector3 GetVelocity() { return m_velocity; }
    Vector3 GetAcceleration() { return m_acceleration; }

    std::string GetName() {return m_name;}

    //Setters
    void SetPosition(const Vector3& position) { m_position = position; }
    void SetVelocity(const Vector3& velocity) { m_velocity = velocity; }
    void SetAcceleration(const Vector3& acceleration) { m_acceleration = acceleration; }
};