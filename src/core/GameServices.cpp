#include "core/Game.h"
#include "core/GameServices.h"
#include "core/GameTypes.h"
#include "physics/SolarSystem.h"


GameState GameServices::GetState() const { return game->GetGameState(); }
// Tools GameServices::GetCurrentTool() const { return game->GetCurrentTool(); }
// void GameServices::SetTool(Tools t)      { game->ChangeCurrentTool(t); }
void GameServices::SetState(GameState s)   { game->ChangeGameState(s); }
void GameServices::SetCursor(bool isVisible) { game->ChangeCursorVisibility(isVisible); }
