#pragma once

#include "input/IAction.h"

class Ray;

class ActionPlaceBody : public IAction {
private:
    Vector3 m_startPosition;
    float m_ghostRadius;

    Vector3 RaycastPlaneIntersection(Ray ray, Vector3 planePoint, Vector3 planeNormal);

    void OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output) override;
    void OnHold(const InputContext& ctx, GameServices& services, OutputContext& output) override;
    void OnJustRelease(const InputContext& ctx, GameServices& services, OutputContext& output) override;

};