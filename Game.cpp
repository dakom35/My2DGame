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

int Game::initVariables()
{
    this->window = nullptr ;
    this->fps_max = 240 ; 
    this->resX = 800 ; 
    this->resY = 600 ;
    this->points = 0 ;
    if (!this->gunshotSoundBuffer.loadFromFile("9mm-pistol-shot-crop.wav"))
    {
        std::cerr << "The file for the gunshotSound buffer is not found \n" ;
        return -1;
    }
    this->painSound.setBuffer(painSoundBuffer); 
        if (!this->painSoundBuffer.loadFromFile("pain-sound-1.wav"))
    {
        std::cerr << "The file for the painSound buffer is not found \n" ;
        return -1;
    }
    this->gunshotSound.setBuffer(gunshotSoundBuffer); 
    if (!this->font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cerr << "The font was not found \n" ;
        return -1 ; 
    }

    this->avg_fps = 0 ; // initialize value to render it first ever frame (see fps_txt)
    this->fps_txt.setFont(font);
    this->fps_txt.setString("FPS = ");
    this->fps_txt.setFillColor(sf::Color::Red);
    this->fps_txt.setStyle(sf::Text::Bold | sf::Text::Underlined);
    this->fps_txt.setCharacterSize(15);
    this->fps_txt.setPosition(0.f,0.f);
    return 0 ; 
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
    this->window = new sf::RenderWindow(this->videoMode, "Aim Training", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps_max); //max_fps

}

void Game::initEnemies()
{
    
    sf::Sprite spriteMonster; 
    sf::RectangleShape enemy;
    int numberOfEnemies = 5 ;
    if(!this->textureMonster.loadFromFile("Images/monster1.png"))
    {
        std::cerr << "The image was not found \n" ;
    }
    spriteMonster.setTexture(this->textureMonster);

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed rnd # generator
    float Xpos,Xpos2,Ypos,Ypos2 ;
    sf::Vector2f size = {80.f,80.f}; 
    sf::Vector2f scale = {1.f,1.f};
    enemy.setSize(size);
    enemy.setScale(scale);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOutlineColor(sf::Color::White);
    enemy.setOutlineThickness(5.f);
    for(int i = 0; i < numberOfEnemies ; i++) 
    {
        Xpos = static_cast<float>(std::rand() % this->videoMode.width+1 - size.x*scale.x); // Numbers between 0 and (width - widthRectangle)
        Ypos = static_cast<float>(std::rand() % this->videoMode.height+1 - size.y*scale.y); // numbers between 0 and (height - heightRectangle)
        Xpos2 = static_cast<float>(std::rand() % this->videoMode.width+1 - size.x*scale.x); // Numbers between 0 and (width - widthMonster)
        Ypos2 = static_cast<float>(std::rand() % this->videoMode.height+1 - size.y*scale.y); // numbers between 0 and (height - heightMonster)
        if(Xpos < 0) Xpos += size.x*scale.x ; // fast way to prevent spawn to the left of window
        if(Ypos < 0 ) Ypos += size.y*scale.y ; // fast way to prevent spawn above of window
        if(Xpos2 < 0) Xpos2 += size.x*scale.x ; // fast way to prevent spawn to the left of window
        if(Ypos2 < 0 ) Ypos2 += size.y*scale.y ; // fast way to prevent spawn above of window
        enemy.setPosition(Xpos,Ypos);
        spriteMonster.setPosition(Xpos2,Ypos2);
        this->enemyVector.push_back(enemy);
        this->enemyVector2.push_back(spriteMonster);
    } 
}



void Game::respawnEnemy(int i, bool isMonster)
{
    /* 
        @brief respawns the Enemy at a random position in the window
        @return void
        @param i is the ennemy's number in the enemyVector
                isMonster says if it's a rectangle or a real monster (sprite)
    */
    float Xpos,Ypos,Xpos2,Ypos2;
    sf::Vector2f position,size,size2,scale,scale2 ;
    sf::RectangleShape enemy = this->enemyVector[i] ;
    sf::Sprite enemy2 = this->enemyVector2[i];
    if(isMonster)
    {
        size2 = this->sizeMonster ;
        scale2 = this->scaleMonster ;
        Xpos2 = static_cast<float>(std::rand() % this->videoMode.width+1 - size2.x*scale2.x); // Numbers between 0 and (width - widthMonster)
        Ypos2 = static_cast<float>(std::rand() % this->videoMode.height+1 - size2.y*scale2.y); // numbers between 0 and (height - heightRectangle)
        if(Xpos2 < 0) Xpos2 += size2.x*scale2.x ; // fast way to prevent spawn to the left of window
        if(Ypos2 < 0 ) Ypos2 += size2.y*scale2.y ; // fast way to prevent spawn above of window
        this->enemyVector2[i].setPosition(Xpos2,Ypos2);
    }
    else
    {
        size = enemy.getSize();  
        scale = enemy.getScale();  
        Xpos = static_cast<float>(std::rand() % this->videoMode.width+1 - size2.x*scale2.x); // Numbers between 0 and (width - widthRectangle) 
        Ypos = static_cast<float>(std::rand() % this->videoMode.height+1 - size.y*scale.y); // numbers between 0 and (height - heightRectangle)  
        if(Xpos < 0) Xpos += size.x*scale.x ; // fast way to prevent spawn to the left of window
        if(Ypos < 0 ) Ypos += size.y*scale.y ; // fast way to prevent spawn above of window
        this->enemyVector[i].setPosition(Xpos,Ypos);
    }   
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
   sf::FloatRect enemyBounds,enemyBounds2 ;
   sf::Rect<float> rectEnemyBounds,rectEnemyBounds2 ;
   //sf::Event event;

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    if(this->ev.type == sf::Event::MouseButtonPressed && this->ev.mouseButton.button == sf::Mouse::Left && !leftClickActive) 
    {  // Fire the shot only if the mouse button was not pressed before
        this->gunshotSound.play();
        leftClickActive = true ;
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window); // Get the current mouse position
        sf::Vector2f floatMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        for(size_t i = 0; i<this->enemyVector.size(); i++) 
        {
            enemyBounds = this->enemyVector[i].getGlobalBounds(); // Get the global bounds of the RectangleShape
            enemyBounds2 = this->enemyVector2[i].getGlobalBounds(); // Get the global bounds of the monster
            
            rectEnemyBounds = sf::Rect(enemyBounds.left, enemyBounds.top, enemyBounds.width, enemyBounds.height); // Convert the FloatRect to Rect
            rectEnemyBounds2 = sf::Rect(enemyBounds2.left, enemyBounds2.top, enemyBounds2.width, enemyBounds2.height) ;
            if(rectEnemyBounds.contains(floatMousePos)) 
            {
                this->painSound.play();
                this->points++; 
                respawnEnemy(i,false);
            }
            if(rectEnemyBounds2.contains(floatMousePos))
            {
                this->painSound.play();
                this->points++; 
                respawnEnemy(i,true); 
            }
        }     
    }  
    else if(this->ev.type == sf::Event::MouseButtonReleased && this->ev.mouseButton.button == sf::Mouse::Left) 
    {       
        leftClickActive = false; // Reset the flag when the mouse button is released 
    }  
}

void Game::update()
{
    this->start = std::chrono::high_resolution_clock::now(); 
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
    static int counter = 0 ; // counts the number of frames up to N
    const int N = 500 ; // number of samples used by the average process
    static float last_fps_avg = 0.f ; // remember last avg_fps once computation is over
    
    // Draw game objects 
    for (const auto& enemy : this->enemyVector) 
    {
        // Access and use the current element directly, useful if enemies are of different types
        this->window->draw(enemy);
    }
    //this->window->draw(this->spriteMonster);
    for (const auto& enemy2 : this->enemyVector2) 
    {
        // Access and use the current element directly, useful if enemies are of different types
        this->window->draw(enemy2);
    }

    this->window->draw(this->fps_txt);
    this->window->display();
    

    this->end = std::chrono::high_resolution_clock::now(); 
    this->fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
    this->avg_fps += fps/N ;  
    if(counter == N-1) // N-1 because the avg_fps increment occured N times
    {
        std::cout << "Average FPS = " << last_fps_avg << "\n";
        counter= 0;
        last_fps_avg = this->avg_fps ;
        this->avg_fps = 0.f ;
    }
    this->fps_txt.setString("FPS = "+std::to_string(last_fps_avg)); 
    
    counter++;
    // std::cout << "FPS = " << this->fps << "\n";


}
