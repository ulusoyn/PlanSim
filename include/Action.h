#pragma once
#include <string>
#include <functional>
#include "GameMode.h"
 
struct Action
{
    std::string name;
    GameMode gamemode;
    std::function<void()> onTrigger;
    std::function<void()> onHold;
    std::function<void()> onRelease;
    bool enabled = true;
};