#include "Game.h"


// Private functions 


// void Game::initVariables()
// {
//     /*
//             // access the member variable window of the current instance of the class 'Game'
//             // 
//     */
//     this->window = nullptr ; 
// }

void Game::initVariables()
{
    this->window = nullptr ;
}

void Game::initWindow()
{
    /*
        sets window settings :
            - res
            - fps
    */
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
                this->window->close(); // really frees memory when closing display (click cross for example)
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                    std::cout << "My2DGame has been closed !!! See you next time !!!" << std::endl ; 
                    break;
        }
    }

}

bool Game::isMousePosInRect(sf::Vector2f rectPos,sf::Vector2f mousePos,sf::Vector2f rectSize,sf::Vector2f scale)
{
    /*
    *   @return bool inclusion : true if mouse's position is in the rectangle

        @args 
                sf::Vector2i rectPos : origin point of rectangle 
                sf::Vector2i mousePos : mouse position
                sf::Vector2f rectSize : rectangle's size 
                sf::Vector2f scale : scaling factor

        @variables
                float rectSizeLengthX : length of rectangle along X axis
                float rectSizeLengthY : length of rectangle along Y axis

        @brief 
                a point M is in a rectangle of origin point A if : 
                    xA <= xM <= xA + xL
                    yA <= yM <= yA + yL 
                with xL being the length of rectangle along X axis
                and yL for the Y axis.
    */
    bool inclusion = false ; // answer to question
    float rectSizeLengthX = rectSize.x * scale.x ;
    float rectSizeLengthY = rectSize.y * scale.y ;
    if(rectPos.x <= mousePos.x <= rectPos.x + rectSizeLengthX 
    && rectPos.y <= mousePos.y <= rectPos.y + rectSizeLengthY ) // see @brief
        inclusion = true ;
    return inclusion ;
}

void Game::updateMousePositions()
{
    /*
        @ return void
        updates the mouse positions :
            - Mouse position relative to window (Vector2i)
    */
   bool inclusion = false ;

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            // Get the current mouse position
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
            sf::Vector2f convertedMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            inclusion = Game::isMousePosInRect(this->enemy.getPosition(),convertedMousePos,this->enemy.getSize(),this->enemy.getScale());
       }
   std::cout << "Mouse pos :" << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n" ;
   if(inclusion == true) 
    {
        std::cout << "Ennemy shot !" << "\n" ;
    }
        
   }

void Game::update()
{
    this->pollEvents(); 
    this->updateMousePositions();

}

void Game::render()
{
    /*
        @return void 
        - clear old frame
        - render objects
        - display frame 
        Renders the game objects .
    */
    this->window->clear(sf::Color::Red);

    // Draw game objects 
    this->window->draw(this->enemy);
    this->window->display();

}
