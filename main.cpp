
#include "Game.h"


int main()
{
    // Init game engine 
    Game game;

    // Game loop
    /* 
    While game is running :
        - prepare next frame (update) 
        - display it (render)     
    */
    while(game.running())
    {
        // Update 
        game.update();

        // Render 
        game.render();
    }

    // End of application 
    return 0;
}