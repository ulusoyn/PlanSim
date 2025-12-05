#include "core/GameServices.h"
#include "input/actions/ActionSelectAndDragBody.h"
#include "input/InputContext.h"
#include "physics/SolarSystem.h"
#include "ui/OutputContext.h"

#include "raymath.h"

std::shared_ptr<CelestialBody> ActionSelectandDragBody::FindClosestBody(const InputContext& ctx, GameServices& services, OutputContext& output){
    // Implementation for dragging the selected body
    float closestDistance = FLT_MAX;
    std::shared_ptr<CelestialBody> closestBody = nullptr;
    Ray startRay = GetMouseRay(ctx.mousePos, ctx.camera);
    std::vector<std::shared_ptr<CelestialBody>>& bodies = services.solarSystem->GetBodies();

    for (auto& body : bodies) {
        RayCollision collision = GetRayCollisionSphere(
            startRay, 
            body->GetPosition(), 
            body->GetRadius()
        );
        if (collision.hit && collision.distance < closestDistance) {
            closestDistance = collision.distance;
            closestBody = body;  // Store the shared_ptr directly
        }
    }

    return closestBody;
}

void ActionSelectandDragBody::OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output){
    output.selectedBodyForGUI = output.highlightedBody;

    output.highlightedBody = nullptr;
}


void ActionSelectandDragBody::OnRelease(const InputContext& ctx, GameServices& services, OutputContext& output){
    std::shared_ptr<CelestialBody> closestBody = FindClosestBody(ctx, services, output);
    output.highlightedBody = closestBody;

}

void ActionSelectandDragBody::OnHold(const InputContext& ctx, GameServices& services, OutputContext& output){
    if (output.highlightedBody == nullptr)
        return; 
    
    Vector2 mousePos = GetMousePosition();

    float depth = Vector3Distance(services.camera->position, output.highlightedBody->GetPosition());

    Ray mouseRay = GetMouseRay(mousePos, ctx.camera);

    Vector3 newPosition = Vector3Add(
        mouseRay.position, 
        Vector3Scale(mouseRay.direction, depth));

    output.highlightedBody->SetPosition(newPosition);
}