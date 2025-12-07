#include "input/actions/ActionChangeToggleMode.h"
#include "core/GameTypes.h"

void ActionChangeToggleMode::OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output){
    auto gameState = services.GetState();

    if(gameState == GameState::CameraControl)
    {
        services.SetState(GameState::EditingMode);
    }
    else if(gameState == GameState::EditingMode)
    {
        services.SetState(GameState::CameraControl);
    }
}