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
    this->window->setFramerateLimit(60); //max_fps

}

void Game::initEnemies()
{
    float Xpos = 200;
    float Ypos = 250 ;
    this->enemy.setPosition(Xpos,Ypos);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setScale(sf::Vector2f(0.6f,0.4f));
    this->enemy.setFillColor(sf::Color::Cyan); 
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(5.f);
}


// constructors / destructors 

Game::Game()
{
    this->initVariables() ; // call order is important here
    this->initWindow();
    this->initEnemies();
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

    //update mouse position
    // Relative to the screen
    //std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n" ; 
    // Relative to the game's window
    std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x 
    << " " << sf::Mouse::getPosition(*this->window).y << "\n" ;
    

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
    this->window->draw(this->enemy);
    this->window->display();

}