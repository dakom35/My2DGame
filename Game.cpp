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
    this->fps_max = 240 ; 
    this->resX = 800 ; 
    this->resY = 600 ;
}

void Game::initWindow()
{
    /*
        sets window settings :
            - res
            - fps
    */
    this->videoMode.height = resY ; 
    this->videoMode.width = resX ; 
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps_max); //max_fps

}

void Game::initEnemies()
{
    sf::RectangleShape enemy;
    int numberOfEnemies = 5 ;
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed rnd # generator
    float Xpos,Ypos ;
    sf::Vector2f size = {100.f,100.f}; 
    sf::Vector2f scale = {0.6f,0.4f};
    enemy.setSize(size);
    enemy.setScale(scale);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(5.f);
    for(int i = 0; i < numberOfEnemies ; i++) 
    {
        Xpos = static_cast<float>(std::rand() % this->videoMode.width+1 - size.x*scale.x); // Numbers between 0 and (width - widthRectangle)
        Ypos = static_cast<float>(std::rand() % this->videoMode.height+1 - size.y*scale.y); // numbers between 0 and (height - heightRectangle)
        if(Xpos < 0) Xpos += size.x*scale.x ; // fast way to prevent spawn to the left of window
        if(Ypos < 0 ) Ypos += size.y*scale.y ; // fast way to prevent spawn above of window
        enemy.setPosition(Xpos,Ypos);
        enemyVector.push_back(enemy);
    } 
}



void Game::respawnEnemy(int i)
{
    /* 
        @brief respawns the Enemy at a random position in the window
        @return void
        @param i is the ennemy's number in the enemyVector
    */
    float Xpos,Ypos;
    sf::Vector2f position,size,scale ;
    sf::RectangleShape enemy = this->enemyVector[i] ;
    position = enemy.getPosition();
    size = enemy.getSize();
    scale = enemy.getScale();

    Xpos = static_cast<float>(std::rand() % this->videoMode.width+1 - size.x*scale.x); // Numbers between 0 and (width - widthRectangle)
    Ypos = static_cast<float>(std::rand() % this->videoMode.height+1 - size.y*scale.y); // numbers between 0 and (height - heightRectangle)
    if(Xpos < 0) Xpos += size.x*scale.x ; // fast way to prevent spawn to the left of window
    if(Ypos < 0 ) Ypos += size.y*scale.y ; // fast way to prevent spawn above of window

    // std::cout << "Origin = " << position.x << " " << position.y
    //             << " width = " << size.x * scale.x << " height = " << size.y * scale.y
    //             << "\n" ;
    this->enemyVector[i].setPosition(Xpos,Ypos);
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

// as long as there is no event to handle...
void Game::pollEvents()
{
    float fps ;

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
            default:  // we don't handle the other event types 
            break;
        }
    }
}


void Game::shootingLogic()
{
    /*
        @return void
        @brief check if user clicks on enemies, if so respawn them elsewhere
    */
   static bool leftClickActive = false ;
   sf::FloatRect floatRect ;
   sf::Rect<float> rect ;
   //sf::Event event;

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    if(this->ev.type == sf::Event::MouseButtonPressed && this->ev.mouseButton.button == sf::Mouse::Left)
    {  // Fire the shot only if the mouse button was not pressed before
        if(!leftClickActive)
        {
            leftClickActive = true ;
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window); // Get the current mouse position
            sf::Vector2f floatMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            for(size_t i = 0; i<enemyVector.size(); i++) 
            {
                floatRect = enemyVector[i].getGlobalBounds(); // Get the global bounds of the RectangleShape
                rect = sf::Rect(floatRect.left, floatRect.top, floatRect.width, floatRect.height); // Convert the FloatRect to Rect
                if(rect.contains(floatMousePos)) 
                {
                    std::cout << "Enemy shot !" << "\n" ;
                    respawnEnemy(i);
                }
            }     
        }
        else if (this->ev.type == sf::Event::MouseButtonReleased && this->ev.mouseButton.button == sf::Mouse::Left) 
        {   // Reset the flag when the mouse button is released     
                leftClickActive = false;
        }
        
    }  
    else if (~sf::Mouse::isButtonPressed(sf::Mouse::Left)) // if left click is not clicked
    {
        leftClickActive = false ;
    }

}

void Game::update()
{
    this->pollEvents(); 
    this->shootingLogic();

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
    this->window->clear(sf::Color::Black);

    // Draw game objects 
    for (const auto& enemy : this->enemyVector) 
    {
        // Access and use the current element directly, useful if enemies are of different types
        this->window->draw(enemy);
    }
    
    this->window->display();

}
