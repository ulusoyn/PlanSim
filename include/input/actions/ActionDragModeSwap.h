#pragma once

#include "input/IAction.h"


class ActionDragToggleMode : public IAction {
private:
    void OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output) override;
};