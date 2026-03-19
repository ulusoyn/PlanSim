#include "physics/SolarSystem.h"
#include "physics/CelestialBody.h"
#include "raymath.h"
#include "core/Constants.h"

SolarSystem::SolarSystem() {
    // Constructor implementation (if needed)
    AddBody("Sun", SimPhysics::EARTH_MASS*10, SimPhysics::EARTH_RADIUS*5, 
        Color{122, 122, 0, 255}, Vector3{0, 0, 0}, Vector3{0, 0, 0});

        
}
void SolarSystem::InitializeBodies() {
    for (auto& body : m_bodies) {
        body->Initialize();
    }
}

void SolarSystem::ApplyGravity(){
for (size_t i = 0; i < m_bodies.size(); i++) {
        for (size_t j = i + 1; j < m_bodies.size(); j++) {
            CelestialBody* bodyA = m_bodies[i].get();
            CelestialBody* bodyB = m_bodies[j].get();

            Vector3 direction = Vector3Subtract(bodyB->GetPosition(), bodyA->GetPosition());
            float distance = Vector3Length(direction);
            
            if (distance < 0.1f) continue;

            float forceMag = (m_gravitationalConstant * bodyA->GetMass() * bodyB->GetMass()) / (distance * distance);
            
            Vector3 forceDir = Vector3Normalize(direction);
            Vector3 forceOnA = Vector3Scale(forceDir, forceMag);
            
            Vector3 forceOnB = Vector3Negate(forceOnA); // The exact opposite force

            bodyA->ApplyForce(forceOnA);
            bodyB->ApplyForce(forceOnB);
        }
    }
}

void SolarSystem::Update(float deltaTime){
    for (const auto& body : m_bodies) {
        body->Update(deltaTime);
    }
}

void SolarSystem::Draw(){
    for(const auto& body : m_bodies){
        body->Draw();
    }
}

void SolarSystem::AddBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity){
    auto body = std::make_unique<CelestialBody>(name, mass, radius, color, position, velocity);
    body->Initialize();  // ← ekle, AddBody zaten InitWindow'dan sonra çağrılıyor
    m_bodies.push_back(std::move(body));
}


void SolarSystem::ClearBodies() {
    m_bodies.clear();
}
