// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#pragma once 

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

        // private functions
        void initVariables();
        void initWindow();


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


