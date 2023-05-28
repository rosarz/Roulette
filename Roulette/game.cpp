#include "game.h"
//Private functions 
//
void game::initVar()
{
	this->window = nullptr; 
	
}

void game::initWindow()
{
	this->videoMode.height = 720; 
	this->videoMode.width = 1280; 
	this->window = new sf::RenderWindow(this->videoMode, "Roulette", sf::Style::Titlebar | sf::Style::Close);
}

//Constructor 
game::game()
{
	this->initVar(); 
	this->initWindow(); 
}
//Deconstructor
game::~game()
{
	delete this->window; 
}

//Accessors 
const bool game::isRunning() const
{
	return this->window->isOpen();
}

//Functions 

void game::pollEvents()
{
    
    while (this->window->pollEvent(this->eve))
    {
        switch (this->eve.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->eve.key.code = sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

//Update the game logic 
void game::update()
{
    this->pollEvents(); 
}

//Visualize all the display things 
void game::render()
{
    /*
    @return void 
    Render the game objects
    - clear old frame 
    - render objects 
    - display frame in window
    */

    this->window->clear(sf::Color(255, 0, 0, 255)); 

    //Draw the game
    this->window->display(); 
}


