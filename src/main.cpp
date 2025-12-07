#include "pch.h"
#include "Game.h"



int main()
{
    Game Game(1440, 900);
    
    

    while (Game.IsRunning())
    {
        Game.Run();

    }
    



    return 0;
}