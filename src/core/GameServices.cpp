#include "core/GameServices.h"
#include "core/Game.h"
#include "physics/SolarSystem.h"



GameState GameServices::GetState() const { return game->GetGameState(); }
void GameServices::SetState(GameState s)   { game->ChangeGameState(s); }
