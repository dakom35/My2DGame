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
    sf::RectangleShape enemy;
    int numberOfEnemies = 5 ;
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed rnd # generator
    float Xpos,Ypos ;
    enemy.setSize(sf::Vector2f(100.f,100.f));
    enemy.setScale(sf::Vector2f(0.6f,0.4f));
    enemy.setFillColor(sf::Color::Red);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(5.f);
    for(int i = 0; i < numberOfEnemies ; i++) 
    {
        Xpos = static_cast<float>(std::rand() % this->videoMode.width+1); // Numbers between 0 and width
        Ypos = static_cast<float>(std::rand() % this->videoMode.height+1); // numbers between 0 and height
        enemy.setPosition(Xpos,Ypos);
        enemyVector.push_back(enemy);
    } 
}

void Game::respawnEnemy()
{
    float Xpos,Ypos;
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed rnd # generator
    Xpos = static_cast<float>(std::rand() % this->videoMode.width+1); // Numbers between 0 and width
    Ypos = static_cast<float>(std::rand() % this->videoMode.height+1); // numbers between 0 and height
    std::cout << "Xpos = " << Xpos << "| Ypos = " << Ypos << "\n" ;
    this->enemyVector[0].setPosition(Xpos,Ypos);
    this->enemyVector[0].setSize(sf::Vector2f(100.f,100.f));
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

// as long as there is not event to handle...
void Game::pollEvents()
{
    // Event polling
    while(this->window->pollEvent(this->ev))
    {
        // we check the event's type...
        switch(this->ev.type)
        {
            case sf::Event::Closed: // closing request
                this->window->close(); // effectively closing
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                    std::cout << "My2DGame has been closed !!! See you next time !!!" << std::endl ; 
                    break;
            // we don't handle the other event types 
            default:
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
    if((rectPos.x <= mousePos.x) &&  (mousePos.x <= (rectPos.x + rectSizeLengthX)) 
    && (rectPos.y <= mousePos.y) && (mousePos.y <= (rectPos.y + rectSizeLengthY)))
    {
        inclusion = true ;
    } 
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
   static int counter = 0 ; // slow down the rate of display of mouse position to 1s
   counter++;

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            // Get the current mouse position
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
            sf::Vector2f convertedMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            inclusion = Game::isMousePosInRect(this->enemyVector[0].getPosition(),convertedMousePos,this->enemyVector[0].getSize(),this->enemyVector[0].getScale());
       }
    if(counter==60)
    {
        std::cout << "Mouse pos :" << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n" ;
        counter=0;
    }
   
   if(inclusion == true) 
    {
        std::cout << "Ennemy shot !" << "\n" ;
        respawnEnemy(); 
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
    this->window->clear(sf::Color::Transparent);

    // Draw game objects 
    for (const auto& enemy : this->enemyVector) 
    {
        // Access and use the current element directly, useful if enemies are of different types
        this->window->draw(enemy);
    }
    
    this->window->display();

}
