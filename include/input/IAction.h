#pragma once

#include "core/GameTypes.h"
#include "input/InputContext.h"
#include "core/GameServices.h"
#include "ui/OutputContext.h"

#include <iostream>

class IAction{
protected:
    virtual void OnTrigger(const InputContext& ctx, GameServices& services, OutputContext& output) {}
    virtual void OnHold(const InputContext& ctx, GameServices& services, OutputContext& output) {}
    virtual void OnRelease(const InputContext& ctx, GameServices& services, OutputContext& output) {}
    virtual void OnJustRelease(const InputContext& ctx, GameServices& services, OutputContext& output) {}


public:
    virtual ~IAction(){}

    void Execute(ActionMode mode, const InputContext& ctx, GameServices& services, OutputContext& output) {
        switch (mode) {
            case ActionMode::Trigger:  OnTrigger(ctx, services, output);  break;
            case ActionMode::Hold:     OnHold(ctx, services, output);     break;
            case ActionMode::Release:  OnRelease(ctx, services, output);  break;
            case ActionMode::JustReleased: OnJustRelease(ctx, services, output);  break;
        
        }
    }
};