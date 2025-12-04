#pragma once
#include <string>
#include <functional>
#include "GameMode.h"
 
struct Action
{
    std::string name;
    std::function<void()> command;
    bool enabled = true;
};