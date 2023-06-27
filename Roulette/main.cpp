#include <iostream>
#include "game.h"
#include "windowRender.h"

int main()
{   
    //Initialize game engine 
    game game; 


    //Game loop 
    while (game.isRunning()) 
    {
        //Update
        game.update();


        //Render
        game.render2();
        game.render();
    }
    return 0; 
}