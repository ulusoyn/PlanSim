
#include "core/Constants.h"
#include "core/GameServices.h"
#include "input/actions/ActionPlaceBody.h"
#include "input/InputContext.h"
#include "physics/SolarSystem.h"
#include "ui/OutputContext.h"


#include "raylib.h"
#include "raymath.h"

#include <string>
Vector3 ActionPlaceBody::RaycastPlaneIntersection(Ray ray, Vector3 planePoint, Vector3 planeNormal)
{
        // 1. Calculate the distance 't' along the ray to the intersection point.
        // a) Dot product of the normal and the difference between plane point and ray origin
        float numerator = Vector3DotProduct(planeNormal, Vector3Subtract(planePoint, ray.position));

        // b) Dot product of the normal and the ray direction
        float denominator = Vector3DotProduct(planeNormal, ray.direction);

        // Safety check: If the ray is parallel to the plane, return the origin.
        if (fabsf(denominator) < 0.0001f) return ray.position;

        // 2. Calculate the distance 't'
        float t = numerator / denominator;

        // 3. Calculate the intersection point P = ray.position + t * ray.direction
        return Vector3Add(ray.position, Vector3Scale(ray.direction, t));
}

void ActionPlaceBody::OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output){
        Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
        Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };

        Ray startRay = GetMouseRay(GetMousePosition(), *(services.camera));

        m_startPosition = RaycastPlaneIntersection(startRay, planePoint, planeNormal);
}

void ActionPlaceBody::OnHold(const InputContext& ctx , GameServices& services, OutputContext& output){

        Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
        Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };
        Ray currentRay = GetMouseRay(GetMousePosition(), *(services.camera));

        // --- 3. Determine the Ghost Point (The current 3D point on the plane) ---
        Vector3 current3DPosition = RaycastPlaneIntersection(currentRay, planePoint, planeNormal);
        
        m_ghostRadius = Vector3Distance(m_startPosition, current3DPosition);

        // Optional: Set a minimum radius to prevent division by zero later
        if (m_ghostRadius < 0.1f) m_ghostRadius = 0.1f;
}

void ActionPlaceBody::OnRelease(const InputContext& ctx , GameServices& services, OutputContext& output){
        int numb = services.solarSystem->GetBodyCount();
        std::string planetName = " Planet" + std::to_string(numb);
        services.solarSystem->AddBody(planetName, SimPhysics::UNIT_MASS,
                m_ghostRadius*SimPhysics::UNIT_DISTANCE, GREEN, m_startPosition, Vector3{0.0f, 0.0f, 0.0f});
}

