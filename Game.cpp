#include "Game.h"


// Private functions 
void Game::initVariables()
{
    this->window = nullptr ;
}

void Game::initWindow()
{
    this->videoMode.height = 600 ; 
    this->videoMode.width = 800 ; 
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Titlebar | sf::Style::Close);

}


// constructors / destructors 

Game::Game()
{
    this->initVariables() ; // call order is important here
    this->initWindow();
}

Game::~Game()
{
    delete this->window ;
}

// Accessors 

const bool Game::running() const 
{
    return this->window->isOpen() ;
}


// Functions 

void Game::pollEvents()
{
    // Event polling
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                    break;
        }
    }

}

void Game::update()
{
    this->pollEvents(); 
}

void Game::render()
{
    /*
        @return void 

        -clear old frame
        -render objects
        -display frame 
        Renders the game objects .


    */
    this->window->clear(sf::Color::Red);

    // Draw game objects 

    this->window->display();
}