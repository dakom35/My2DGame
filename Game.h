// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions


/*
    Class that acts as the game engine 
*/

class Game
{
    private : 
        /*
            - window : summons a system window for the game
            - videoMode : 
                --> width
                --> height
                --> bitsPerPixel
                    ... of video
            - ev : any system event such as :
                -  mouse/keyboard input
                -  game closing
                
        */
        sf::RenderWindow* window ;
        sf::VideoMode videoMode ; 
        sf::Event ev ; // Every event 

        //Mouse positions
        sf::Vector2i mousePosWindow ; // this pos of mouse is relative to game's window 

        //Game objects
        std::vector<sf::RectangleShape> enemyVector;




        // private functions
        void initVariables();
        void initWindow();
        void initEnemies();
        void respawnEnemy(int i);


    public : 
        // Constructors / Destructors 

        Game();
        virtual ~Game();

        // Accessors
        const bool running() const ; 

        // Functions 
        void pollEvents();
        void update(); 
        void render(); 
        void updateEnemyStatus();

};


#endif // GAME_H


