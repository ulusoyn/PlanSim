#include "physics/CelestialBody.h"

#include "raymath.h"

CelestialBody::CelestialBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity){
    m_name = name;
    m_mass = mass;
    m_radius = radius;
    m_color = color;
    m_position = position;
    m_velocity = velocity;

    m_acceleration = {0.0f, 0.0f, 0.0f};
    m_forceAccumulator = {0.0f, 0.0f, 0.0f};
}


void CelestialBody::Update(float deltaTime){
    if (m_mass > 0) {
        m_acceleration.x = m_forceAccumulator.x / m_mass;
        m_acceleration.y = m_forceAccumulator.y / m_mass;
        m_acceleration.z = m_forceAccumulator.z / m_mass;
    }

    // 2. Update Velocity: v = v + (a * dt)
    Vector3 deltaV = Vector3Scale(m_acceleration, deltaTime);
    m_velocity = Vector3Add(m_velocity, deltaV);

    // 3. Update Position: p = p + (v * dt)
    Vector3 deltaP = Vector3Scale(m_velocity, deltaTime);
    m_position = Vector3Add(m_position, deltaP);

    if (m_position.x > m_limit || m_position.x < -m_limit)
    {
        m_velocity.x *= -0.9f;
    }
    if (m_position.y > m_limit || m_position.y < -m_limit)
    {
        m_velocity.y *= -0.9f;
    }
    if (m_position.z > m_limit || m_position.z < -m_limit)
    {
        m_velocity.z *= -0.9f;
    }

    // 4. Reset Forces
    // We must clear the force accumulator every frame, otherwise forces build up forever!
    m_forceAccumulator = { 0.0f, 0.0f, 0.0f };
}

// --- Draw (The Render Engine) ---
void CelestialBody::Draw() {
    DrawSphereEx(m_position, m_radius, 64, 64, BLUE);
    
    // Optional: Draw a wireframe around it to make it look "techy"
    DrawWires(m_color);
}

void CelestialBody::DrawWires(Color color){
    DrawSphereWires(m_position, m_radius + 0.1f, 32, 32, Fade(color, 0.6f));
}

// --- Physics Helpers ---
void CelestialBody::ApplyForce(Vector3 force) {
    m_forceAccumulator = Vector3Add(m_forceAccumulator, force);
}
