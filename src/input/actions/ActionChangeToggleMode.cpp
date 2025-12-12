#include "input/actions/ActionChangeToggleMode.h"
#include "core/GameTypes.h"
#include "core/GameServices.h"

void ActionChangeToggleMode::OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output){
    auto gameState = services.GetState();

    if(gameState == GameState::CameraControl)
    {
        services.SetState(GameState::EditingMode);
        services.SetCursor(true);
    }
    else if(gameState == GameState::EditingMode)
    {
        services.SetState(GameState::CameraControl);
        services.SetCursor(false);
    }
}