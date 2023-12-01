// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions
#include <chrono> // for FPS measurements



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
        //sf::Clock clock ; 
        int fps_max  ; // maximum fps rate
        int resX ; // X resolution
        int resY  ; // Y resolution
        unsigned int points ; 
        float fps ; // fps calculated with 1 frame
        float avg_fps ; // average fps measure performed on multiple frames,
                        // a few instructions are ignored => increases inacurracy
        sf::SoundBuffer gunshotSoundBuffer;
        sf::SoundBuffer painSoundBuffer;
        sf::Sound gunshotSound; // sound of firing weapon
        sf::Sound painSound ; // sound of the enemy dying
        std::chrono::high_resolution_clock::time_point start; // for fps measurement
        std::chrono::high_resolution_clock::time_point end; // for fps measurement

        //Mouse positions
        sf::Vector2i mousePosWindow ; // this pos of mouse is relative to game's window 

        //Game objects
        std::vector<sf::RectangleShape> enemyVector;
        std::vector<sf::Sprite> enemyVector2 ;
        sf::Vector2f sizeMonster = {80.f,80.f} ; 
        sf::Vector2f scaleMonster = {1.f,1.f}; 
        sf::Texture textureMonster ;


        // Writing on screen
        sf::Font font; // font for every text in HUD
        sf::Text fps_txt ;





        // private functions
        int initVariables();
        void initWindow();
        void initEnemies();
        void respawnEnemy(int i,bool monster);


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
        void shootingLogic();

};


#endif // GAME_H