#pragma once
#include "IAction.h"

class ActionPlaceBody : public IAction {
private:
    Vector3 m_startPosition;
    float m_ghostRadius;

    Vector3 RaycastPlaneIntersection(Ray ray, Vector3 planePoint, Vector3 planeNormal);

    void OnTrigger(const InputContext& ctx , GameServices& services) override;
    void OnHold(const InputContext& ctx, GameServices& services) override;
    void OnRelease(const InputContext& ctx, GameServices& services) override;
public:
    ~ActionPlaceBody() override;
    ActionPlaceBody();

    void Execute(ActionMode actionMode, const InputContext& ctx , GameServices& services) override;
};