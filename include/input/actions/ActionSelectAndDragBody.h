#pragma once

#include "input/IAction.h"
#include <memory>

class CelestialBody;

class ActionSelectandDragBody : public IAction {
private:
    void OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output) override;
    void OnHold(const InputContext& ctx, GameServices& services, OutputContext& output) override;
    void OnRelease(const InputContext& ctx, GameServices& services, OutputContext& output) override;

    std::shared_ptr<CelestialBody> FindClosestBody(const InputContext& ctx, GameServices& services, OutputContext& output);

};