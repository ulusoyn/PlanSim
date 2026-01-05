#include "input/actions/ActionChangeToggleMode.h"
#include "core/GameTypes.h"

void ActionChangeToggleMode::OnTrigger(const InputContext& ctx , GameServices& services, OutputContext& output){
    auto gameState = services.GetState();

    if(gameState == GameState::EditingMode)
    {
        services.SetState(GameState::CreationMode);
    }
    else if(gameState == GameState::CreationMode)
    {
        services.SetState(GameState::EditingMode);
    }
}