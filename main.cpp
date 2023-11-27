
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
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    int counter = 0 ;
    int N = 100 ;

    float fps,avg_fps=0;
    while(game.running())
    {
        start = std::chrono::high_resolution_clock::now(); 
        // Update 
        game.update();

        // Render 
        game.render();
        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        avg_fps += fps/N ;
        if(counter == N){
            std::cout << "Average FPS = " << avg_fps << "\n";
            counter=0;
            avg_fps = 0.f ;
        }
        counter++;
    }

    // End of application 
    return 0;
}