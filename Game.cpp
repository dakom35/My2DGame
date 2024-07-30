#include "Game.h"
#include "wtypes.h" #TODO : see if it works on Linux, make a bugs.txt

// Private functions 

int Game::initVariables()
{
    sf::Color semiTransparentGreen(64, 255, 64, 128);
    this->window = nullptr ;
    this->fps_max = 60 ; 
    this->resX = 800 ;
    this->resY = 600 ;

    this->score = 0 ;
    this->avg_fps = 0 ; // initialize value to render it first ever frame (see fps_txt)

    // Set music
    if (!this->music1Buf.loadFromFile("Sounds/Phobos.wav")){
        std::cerr << "The file for the music is not found" << std::endl ;
        return -1;
    }
    this->music1.setBuffer(music1Buf);
    this->music1.play(); 
    this->music1.setLoop(true);

    // Set weapon sound
    if (!this->gunshotBuf.loadFromFile("Sounds/9mm-pistol-shot-crop.wav")){
        std::cerr << "The file for the gunshot's sound buffer is not found" << std::endl ;
        return -1;
    }
    this->gunshot.setBuffer(gunshotBuf); 
    this->gunshot.setVolume(50.f);

    // Set monster1 sound
    if (!this->screamMonster1Buf.loadFromFile("Sounds/monster1bis.wav")){
        std::cerr << "The file for monster1's scream is not found" << std::endl ;
        return -1;
    }
    this->screamMonster1.setBuffer(screamMonster1Buf);

    // Set monster2 sound
    if (!this->screamMonster2Buf.loadFromFile("Sounds/monster2.wav")){
        std::cerr << "The file for monster2's scream is not found" << std::endl ;
        return -1;
    }
    this->screamMonster2.setBuffer(screamMonster2Buf);

    
    if (!this->font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cerr << "The font was not found" << std::endl ;
        return -1 ; 
    }
//  Text (const String &string, const Font &font, unsigned int characterSize=30)
    this->fps_txt = sf::Text("FPS = ",font,15);
    this->fps_txt.setFillColor(semiTransparentGreen);
    this->score_txt = sf::Text("Score = ",font,15);
    this->score_txt.setFillColor(semiTransparentGreen);
    this->score_txt.setPosition(0.f,20.f);
    return 0 ; 
}

void Game::initWindow()
{
    /*
        sets window settings :
            - res
            - fps
    */

    GetDesktopResolution(this->resX, this->resY);
    this->videoMode.height = this->resY ; 
    this->videoMode.width = this->resX ; 
    // sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize
    this->window = new sf::RenderWindow(this->videoMode, "Aim Training", sf::Style::Fullscreen);
    this->window->setFramerateLimit(fps_max); //max_fps
}

void Game::initEnemies()
{
     
    sf::Sprite spriteMonster1,spriteMonster2 ;
    int numberOfEnemies = 4 ;
    //int enemyCategories = 3 ; // rectangle,monster1 and monster2
    if(!this->textureMonster1.loadFromFile("Images/monster1.png"))
    {
        std::cerr << "The image was not found \n" ;
    }
    spriteMonster1.setTexture(this->textureMonster1);
    if(!this->textureMonster2.loadFromFile("Images/monster2.png"))
    {
        std::cerr << "The image was not found \n" ;
    }
    spriteMonster2.setTexture(this->textureMonster2);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed rnd # generator
    float Xpos,Ypos ;
    // type conversions mandatory to make arithmetic operations with std::rand()
    this->sizeMonster1 = {static_cast<int>(textureMonster1.getSize().x),static_cast<int>(textureMonster1.getSize().y)}; 
    this->sizeMonster2 = {static_cast<int>(textureMonster2.getSize().x),static_cast<int>(textureMonster2.getSize().y)};
    for(int i = 0 ; i < numberOfEnemies ; i++)
    {
        Xpos = static_cast<float>(std::rand() % this->resX - this->sizeMonster1.x); // Numbers between 0 and (width - widthMonster)
        Ypos = static_cast<float>(std::rand() % this->resY - this->sizeMonster1.y); // numbers between 0 and (height - heightMonster)
        if(Xpos < 0) Xpos += this->sizeMonster1.x ; // fast way to prevent spawn to the left of window
        if(Ypos < 0 ) Ypos += this->sizeMonster1.y ; // fast way to prevent spawn above of window
        spriteMonster1.setPosition(Xpos,Ypos);
        this->enemyMonster1Vector.push_back(spriteMonster1);
    }
    for(int i = 0 ; i < numberOfEnemies ; i++)
    {
        Xpos = static_cast<float>(std::rand() % this->resX - this->sizeMonster2.x); // Numbers between 0 and (width - widthMonster)
        Ypos = static_cast<float>(std::rand() % this->resY - this->sizeMonster2.y); // numbers between 0 and (height - heightMonster)
        
        if(Xpos < 0) Xpos += this->sizeMonster2.x ; // fast way to prevent spawn to the left of window
        if(Ypos < 0 ) Ypos += this->sizeMonster2.y ; // fast way to prevent spawn above of window
        spriteMonster2.setPosition(Xpos,Ypos);
        this->enemyMonster2Vector.push_back(spriteMonster2);
    }
}



void Game::respawnEnemy(int i, int monsterNumber)
{
    /* 
        @brief respawns the Enemy at a pseudo-random position in the window
        @return void
        @param i is the ennemy's number in the enemyRectangleVector
                monsterNumber : 
                                1 -> monster1
                                2 -> monster2
    */
    float Xpos,Ypos;

    switch(monsterNumber)
    {
        case 1 :     
            Xpos = static_cast<float>(hash() % this->resX - this->sizeMonster1.x); // Numbers between 0 and (width - widthMonster)
            Ypos = static_cast<float>(hash() % this->resY - this->sizeMonster1.y); // numbers between 0 and (height - heightRectangle)
            if(Xpos < 0) Xpos += this->sizeMonster1.x ; // fast way to prevent spawn to the left of window
            if(Ypos < 0 ) Ypos += this->sizeMonster1.y ; // fast way to prevent spawn above of window
            this->enemyMonster1Vector[i].setPosition(Xpos,Ypos);
            break;
        case 2 : 
            Xpos = static_cast<float>(hash() % this->resX - this->sizeMonster2.x); // Numbers between 0 and (width - widthMonster)
            Ypos = static_cast<float>(hash() % this->resY - this->sizeMonster2.y); // numbers between 0 and (height - heightRectangle)
            if(Xpos < 0) Xpos += this->sizeMonster2.x ; // fast way to prevent spawn to the left of window
            if(Ypos < 0 ) Ypos += this->sizeMonster2.y ; // fast way to prevent spawn above of window
            this->enemyMonster2Vector[i].setPosition(Xpos,Ypos);
            break;
        default:
            std::cerr << "Invalid choice in switch/case" << std::endl;
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
                    std::cout << "Aim Training has been closed !!! See you next time !!!" << std::endl ; 
                    break;
            case sf::Event::MouseButtonPressed  : 
                if(this->ev.mouseButton.button == sf::Mouse::Left) // shoot weapon
                    shootingLogic(true);
            case sf::Event::MouseButtonReleased :
                if(this->ev.type == sf::Event::MouseButtonReleased && this->ev.mouseButton.button == sf::Mouse::Left)
                    shootingLogic(false);

            default:  // we don't handle the other event types 
            break;
        }
    }
}


void Game::shootingLogic(bool isleftClickPressed)
{
    /*
        @return void
        @brief check if user clicks on enemies, if so respawn them elsewhere
    */

   static bool isLeftClickActive = false ;
   sf::FloatRect monster1Bounds,monster2Bounds ;
   sf::Rect<float> rectMonster1Bounds,rectMonster2Bounds;
    if(isleftClickPressed && !isLeftClickActive) // Fire the shot only if the mouse button was not pressed before
    {  
        this->gunshot.play();
        isLeftClickActive = true ;
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window); // Get the current mouse position
        sf::Vector2f floatMousePos(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
        for(size_t i = 0; i<this->enemyMonster1Vector.size(); i++) 
        {
            monster1Bounds = this->enemyMonster1Vector[i].getGlobalBounds(); // Get the global bounds of the monster1
            monster2Bounds = this->enemyMonster2Vector[i].getGlobalBounds(); // Get the global bounds of the monster2
            // type conversion : FloatRect -> Rect (to use contains())
            rectMonster1Bounds = sf::Rect(monster1Bounds.left, monster1Bounds.top, monster1Bounds.width, monster1Bounds.height);
            rectMonster2Bounds = sf::Rect(monster2Bounds.left, monster2Bounds.top, monster2Bounds.width, monster2Bounds.height);
            if(rectMonster1Bounds.contains(floatMousePos))
            {
                this->screamMonster1.play();
                this->score++; 
                respawnEnemy(i,1); 
            }
            if(rectMonster2Bounds.contains(floatMousePos))
            {
                this->screamMonster2.play();
                this->score++; 
                respawnEnemy(i,2); 
            }
        }     
    }  
    else
    {       
        isLeftClickActive = false; // Reset the flag when the mouse button is released 
    }  
}

void Game::update()
{
    this->start = std::chrono::high_resolution_clock::now(); 
    this->pollEvents(); 
    //this->shootingLogic();
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
    this->renderEnemies();
    this->renderHUD(); 
    this->window->display();
    this->end = std::chrono::high_resolution_clock::now(); 
    this->fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
    this->avg_fps += fps/N ;  
    if(counter == N-1) // N-1 because the avg_fps increment occured N times
    {
        counter= 0;
        last_fps_avg = this->avg_fps ;
        this->avg_fps = 0.f ;
    }
    this->fps_txt.setString("FPS = "+std::to_string(static_cast<int>(last_fps_avg))); 
    counter++;
}

void Game::renderHUD()
/*
    Function to render every HUD objects (FPS,score,...)
*/
{
    this->score_txt.setString("Score = "+std::to_string(score));
    this->window->draw(this->fps_txt);
    this->window->draw(this->score_txt);

}

void Game::renderEnemies()
/*
    Function to render every enemy 
*/
{
    for (const auto& monster : this->enemyMonster1Vector) 
    {
        this->window->draw(monster);
    }
    for (const auto& monster : this->enemyMonster2Vector) 
    {
        this->window->draw(monster);
    }
}

int Game::hash()
{
    /*
    A hash function to get a fast random number generator
     */
    static int a = std::rand(); // seed rnd number generator (only done once)
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
    SetProcessDPIAware();
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;
}
