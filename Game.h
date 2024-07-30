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
        int resX ; // X resolution of the game's window
        int resY  ; // Y resolution of the game's window
        unsigned int score ; // score of the player
        float fps ; // fps calculated with 1 frame
        float avg_fps ; // average fps measure performed on multiple frames,
                        // a few instructions are ignored => increases inacurracy
        sf::SoundBuffer gunshotBuf; // gun firing sound
        sf::SoundBuffer screamMonster1Buf,screamMonster2Buf; // death screams of the monsters
        sf::SoundBuffer music1Buf ; 
        sf::Sound gunshot; // sound of firing weapon
        sf::Sound screamMonster1,screamMonster2 ; // sound of the enemy dying
        sf::Sound music1 ; // music you hear all the time
        std::chrono::high_resolution_clock::time_point start; // for fps measurement
        std::chrono::high_resolution_clock::time_point end; // for fps measurement

        //Mouse positions
        sf::Vector2i mousePosWindow ; // this pos of mouse is relative to game's window 

        //Game objects
        //std::vector<sf::RectangleShape> enemyRectangleVector;
        std::vector<sf::Sprite> enemyMonster1Vector ; // round brown monster
        std::vector<sf::Sprite> enemyMonster2Vector ; // snake-like monster
        sf::Texture textureMonster1,textureMonster2 ;
        sf::Vector2i sizeMonster1,sizeMonster2;


        // Writing on screen (HUD)
        sf::Font font; // font for every text in HUD
        sf::Text fps_txt ;
        sf::Text score_txt ;

        // private functions
        int initVariables();
        void initWindow();
        void initEnemies();
        void respawnEnemy(int i, int monsterNumber);
        int hash(); 


    public : 
        // Constructors / Destructors 

        Game();
        virtual ~Game();

        // Accessors
        const bool running() const ; 

        // Functions 
        void pollEvents();
        void update(); 
        void shootingLogic(bool isleftClickPressed);

            // render functions
            void render();
            void renderHUD(); 
            void renderEnemies();
};


// useful functions I don't know where to put yet
void GetDesktopResolution(int& horizontal, int& vertical);



#endif // GAME_H