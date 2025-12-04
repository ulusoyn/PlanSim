#pragma once
#include "InputContext.h"
#include "GameServices.h"
#include "GameTypes.h"

class IAction{
protected:
    virtual void OnTrigger(const InputContext& ctx, GameServices& services) {}
    virtual void OnHold(const InputContext& ctx, GameServices& services) {}
    virtual void OnRelease(const InputContext& ctx, GameServices& services) {}

public:
    virtual ~IAction();    

    void Execute(ActionMode mode, const InputContext& ctx, GameServices& services) {
        switch (mode) {
            case ActionMode::Trigger:  OnTrigger(ctx, services);  break;
            case ActionMode::Hold:     OnHold(ctx, services);     break;
            case ActionMode::Release:  OnRelease(ctx, services);  break;
        }
    }
};