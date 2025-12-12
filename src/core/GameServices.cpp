#include "core/Game.h"
#include "core/GameServices.h"
#include "core/GameTypes.h"
#include "physics/SolarSystem.h"


GameState GameServices::GetState() const { return game->GetGameState(); }
void GameServices::SetState(GameState s)   { game->ChangeGameState(s); }
void GameServices::SetCursor(bool isVisible) { game->ChangeCursorVisibility(isVisible); }
