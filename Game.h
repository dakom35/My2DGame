// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>


/*
    Class that acts as the game engine 
*/

class Game
{
    private : 

        // Variables
        // Window 
        sf::RenderWindow* window ;
        sf::VideoMode videoMode ; 
        sf::Event ev ;

        //Mouse positions
        sf::Vector2i mousePosWindow ; // pos of mouse relative to game's window 

        //Game objects
        sf::RectangleShape enemy ;


        // private functions
        void initVariables();
        void initWindow();
        void initEnemies();


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

};


#endif // GAME_H


